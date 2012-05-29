#pragma once
#include <Simulation/Core/IUpdateable.h>
#include <Simulation/Geometry/Geometry.h>
#include <Simulation/Geometry/Primitives/Hexahedron.h>
#include <Simulation/Geometry/Primitives/Sphere.h>
#include <map>
#include <functional>

namespace IBDS{
  
enum OctreeNodeId{
  //   xyz  when x==0 => x = width/2 ...
  NODE_000=0,
  NODE_001=1,
  NODE_010=2,
  NODE_011=3,
  NODE_100=4,
  NODE_101=5,
  NODE_110=6,
  NODE_111=7,
  NODE_ROOT=8
};
class BoundingVolume{
  AABB  & _aabb;
public:
  BoundingVolume(AABB  & aabb):_aabb(aabb){}
  Classification classify(Geometry & geometry) const {
    Vector3D center;
    _aabb.getCenter(center);
    Real radius;
    radius = (_aabb.min-_aabb.max).length();

    return geometry.classify(center,radius);
  }
};


class Octree : public virtual ISimulationObject{
private:
  ///< The id of the node
  const OctreeNodeId _id;
  ///< The depth of the tree from this node ( 0 => leaf leaf !=> 0)
  unsigned int _depth;
  ///< The level at which this node is (0 is root)
  unsigned int _level;
  ///< The classfication (inside, outside or both)
  Classification _classfication;
  ///< The axis align boundary box in object coordinats
  AABB _aabb;
  BoundingVolume _boundingVolume;
  ///< The children
  //std::map<OctreeNodeId, Octree*> _children;
  Octree ** _children;
  ///< The geometry that this octree represents
  Geometry & _geometry;

  /**
   * \brief private Constructor.
   *
   * \param id                The node identifier.
   * \param [in,out]  parent  The parent.
   */
  Octree(OctreeNodeId id, Octree & parent);

  /**
   * \brief Refines this object.
   * 				this central method refines the octree to the desired depth
   */
  void refine();

  /**
   * \brief Creates a child node.
   *
   * \param id  The node identifier.
   *
   * \return  null if it fails, else.
   */
  Octree * createChild(OctreeNodeId id);
  
  void setNode(Octree * node);

protected:

  /**
   * \brief Initializes the object.
   * 				refines the octree to the requested level and prunes the tree
   *
   * \return  true if it succeeds, false if it fails.
   */
  bool initializeObject();

  /**
   * \brief Cleanup object.
   * 				deletes all children of this octree
   */
  void cleanupObject();

  /**
   * \brief Instanciates an octree node.  this is a factory method
   * 				used if subclasses want to supply a different octree implementation.
   *
   * \param id                  The node identifier.
   * \param [in,out]  geometry  The geometry.
   *
   * \return  null if it fails, else.
   */
  virtual Octree * instanciate(OctreeNodeId id, Geometry & geometry);

  /**
   * \brief Deletes all the children of this tree recursively.
   */
  void deleteChildren();
   /**
   * \brief Classifies this octreenode. if it is on the finest level it calls classifyGeometrically
   * 				else it calls classifyByChildNodes
   */
  void classify();

  
public:

  /**
   * \brief Constructor.
   *        creates a octree from the geometry which will be refined to depth when initialized
   * \param depth               The depth.
   * \param [in,out]  geometry  The geometry.
   */
  Octree( Geometry & geometry,int depth);

  /**
   * \brief classifies the current node geometrically.  
   *       may be overriden by subclasses
   *
   */
  virtual Classification  classifyGeometrically() const;

  /**
   * \brief Classifies this node by its children by child nodes.
   */
  Classification classifyByChildNodes() const;

 
  
  OctreeNodeId getId()const;
  unsigned int getDepth()const;
  const AABB & getAABB()const;
  void getCenter(Vector3D & c_ocs)const;
  Classification getClassification()const;
  bool isLeaf()const;
  unsigned int getLevel()const;
  Octree * getNode(OctreeNodeId id);
  Geometry & getGeometry()const;


  
  void foreachChild(std::function<void (Octree*)> f);
  void foreachChildOfLevel(unsigned int level, std::function<void (Octree*)> f);
  void foreach(std::function<void (Octree*)> f);
  void foreachLeaf(std::function<void (Octree*)> f);
};



}
#pragma once
//#include <simulation/core/IUpdateable.h>
#include <simulation.geometry/Geometry.h>
#include <simulation.geometry/boundingVolumes/BoundingVolume.h>
#include <map>
#include <functional>

namespace nspace{
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

  class Octree : public ISimulationObject{
    TYPED_OBJECT(Octree)
  private:
    Geometry & _geometry;
    ///< The bounding volume factory is same for all nodes of an octree
    BoundingVolumeFactory & _boundingVolumeFactory;
    ///< The id of the node
    const OctreeNodeId _id;
    ///< The depth of the tree from this node ( 0 => leaf leaf !=> 0)
    unsigned int _depth;
    ///< The level at which this node is (0 is root)
    unsigned int _level;
    ///< The classfication (inside, outside or both)
    Classification _classfication;
    ///< The aabb representing the dimension of this octree node
    BoundingBox _aabb;
    ///< The bounding volume used for collision and classification
    BoundingVolume * _boundingVolume;
    ///< The children
    Octree ** _children;

    /**
    * \brief private Constructor.
    *
    * \param id                The node identifier.
    * \param [in,out]  parent  The parent.
    */
    Octree(OctreeNodeId id, Octree & parent);

    /**
    * \brief Refines this octree.
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

    /**
    * \brief Sets a node.
    *
    * \param [in,out] node If non-null, the node.
    */
    void setNode(Octree * node);

    /**
    * \brief Calculates the depth.
    *
    *
    */
    void calculateDepth();

  protected:
    void createBoundingVolume();
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
    * \brief Deletes all the children of this tree recursively.
    */
    void deleteChildren();
    /**
    * \brief Classifies this octreenode. if it is on the finest level it calls classifyGeometrically
    * 				else it calls classifyByChildNodes
    */
    void classify();

  public:
    void afterStep(Real t, Real h){
      reset();
    }
    ///< The type ("Octree")
    static const Type::TypeId type;

    /**
    * \brief Gets the collision type.
    *
    *
    * \return The collision type.
    */
    const Type::TypeId getCollisionType()const;

    void update();
    void reset();

    const Octree * child(OctreeNodeId i)const;
    ~Octree();
    BoundingVolume & getBoundingVolume();
    BoundingVolume & getBoundingVolume()const;

    Geometry & getGeometry(){return _geometry;}

    /**
    * \brief Constructor. creates a octree from the geometry which will be refined to depth when
    *  initialized.
    *
    * \param [in,out] geometry              The geometry.
    * \param depth                          The depth.
    * \param [in,out] boundingVolumeFactory The bounding volume factory.
    * \param precision                      (optional) the precision (zero means as exact as possible).
    */
    Octree( Geometry & geometry,int depth, BoundingVolumeFactory & boundingVolumeFactory);

    /**
    * \brief classifies the current node geometrically.
    *
    */
    Classification  classifyGeometrically()const;

    /**
    * \brief Classifies this node by its children by child nodes.
    */
    Classification classifyByChildNodes() const;

    OctreeNodeId getId()const;
    unsigned int getDepth()const;
    const BoundingBox & getBoundingBox()const;
    void getCenter(Vector3D & c_ocs)const;
    Classification getClassification()const;
    bool isLeaf()const;
    unsigned int getLevel()const;
    Octree * getNode(OctreeNodeId id);

    void foreachChild(std::function<void (Octree*)> f);
    void foreachChildOfLevel(unsigned int level, std::function<void (Octree*)> f);
    void foreach(std::function<void (Octree*)> f);
    void foreachLeaf(std::function<void (Octree*)> f);
  };
}

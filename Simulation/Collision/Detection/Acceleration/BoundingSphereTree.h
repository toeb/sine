#pragma once
#include <Simulation/Core/IUpdateable.h>
#include <Simulation/Geometry/Geometry.h>
#include <Simulation/Geometry/Primitives/Sphere.h>
#include <map>
#include <functional>
#include <Simulation/Collision/Detection/Acceleration/Octree.h>

namespace IBDS{

class BoundingSphereHierarchy: public virtual IUpdatable, public virtual Sphere{
private:
  int level;
  bool leaf;
  OctreeNodeId nodeId;
  Geometry & _geometry;
  BoundingSphereHierarchy(Geometry & geometry);
  ~BoundingSphereHierarchy();
  std::map<OctreeNodeId,BoundingSphereHierarchy*> _children;
  void refine(int maxLevel);
public:
  bool allOnSameSide();
  int getLevel()const;
  static BoundingSphereHierarchy * create(Geometry & geometry, int depth);
  bool isLeaf()const;
  BoundingSphereHierarchy * get(OctreeNodeId nodeId);
  void set(BoundingSphereHierarchy * node);
  void setLeaf();
  void update(Real t, Real dt);
  void for_each_in_level(int level,std::function<void (BoundingSphereHierarchy*)> f);  
  void for_each_child(std::function<void (BoundingSphereHierarchy*)> f);
  void for_each(std::function<void (BoundingSphereHierarchy*)> f);
};
}
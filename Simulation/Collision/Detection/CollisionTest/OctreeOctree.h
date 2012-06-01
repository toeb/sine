#pragma once
#include <Simulation/Collision/Detection/CollisionTest/CollisionTest.h>
#include <Simulation/Collision/Detection/Acceleration/Octree.h>
#include <Simulation/Collision/Detection/CollisionTest/SphereSphere.h>
#include <Simulation/Geometry/BoundingVolumes/BoundingSphere.h>

namespace IBDS{
class OctreeOctree : public CollisionTest{
private:
  SphereSphere sphereTest;
public:
  const TypeId getTypeA()const;
  const TypeId getTypeB()const;
   bool testCollision(const ICollidable & a, const ICollidable & b, Collision * collision)const;
   bool testCollision(const Octree & a, const Octree & b, Collision * collision)const;

};


}
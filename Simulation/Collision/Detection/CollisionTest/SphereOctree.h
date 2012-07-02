#pragma once
#include <Simulation/Collision/Detection/CollisionTest/CollisionTest.h>
#include <Simulation/Geometry/BoundingVolumes/BoundingOctree.h>
#include <Simulation/Collision/Detection/CollisionTest/SphereSphere.h>
#include <Simulation/Geometry/BoundingVolumes/BoundingSphere.h>

namespace IBDS{
class SphereOctree : public CollisionTest{
private:
  SphereSphere test;
public:
  const TypeId getTypeA()const;
  const TypeId getTypeB()const;
  bool testCollision(const ISimulationObject & a, const ISimulationObject & b, Collision * collision)const;
  bool testCollision(const Sphere & a, const Octree & b, Collision * collision)const;
};


}
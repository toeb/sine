#pragma once
#include <Simulation/Collision/Detection/CollisionTest/CollisionTest.h>
#include <Simulation/Geometry/BoundingVolumes/BoundingOctree.h>
#include <Simulation/Collision/Detection/CollisionTest/SpherePlane.h>
#include <Simulation/Geometry/BoundingVolumes/BoundingSphere.h>

namespace IBDS{
class OctreePlane : public CollisionTest{
private:
  SpherePlane test;
public:
  const TypeId getTypeA()const;
  const TypeId getTypeB()const;
  bool testCollision(const ISimulationObject & a, const ISimulationObject & b, Collision * collision)const;
  bool testCollision(const Octree & a, const Plane & b, Collision * collision)const;

};


}
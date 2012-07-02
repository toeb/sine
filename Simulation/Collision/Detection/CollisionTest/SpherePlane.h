#pragma once

#include <Simulation/Collision/Detection/CollisionTest/CollisionTest.h>
#include <Simulation/Geometry/Plane.h>
#include <Simulation/Geometry/Primitives/Sphere.h>

namespace IBDS{
class SpherePlane : public CollisionTest{
public:
  const TypeId getTypeA()const;
  const TypeId getTypeB()const;
  bool testCollision(const ISimulationObject & a, const ISimulationObject & b, Collision * collision)const;
  bool testCollision(const Sphere & sphere, const Plane & plane, Collision * col)const;
};
}
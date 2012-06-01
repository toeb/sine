#pragma once

#include <Simulation/Collision/Detection/CollisionTest/CollisionTest.h>
#include <Simulation/Geometry/Plane.h>
#include <Simulation/Geometry/Primitives/Sphere.h>

namespace IBDS{
class SpherePlane : public CollisionTest{
public:
  const TypeId getTypeA()const;
  const TypeId getTypeB()const;
  bool testCollision(const ICollidable & a, const ICollidable & b, Collision * collision)const;
};
}
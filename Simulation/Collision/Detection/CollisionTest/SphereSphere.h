#pragma once
#include <Simulation/Collision/Collision.h>
#include <Simulation/Geometry/Primitives/Sphere.h>
#include <Simulation/Collision/Detection/CollisionTest/CollisionTest.h>

namespace IBDS{
struct SphereSphere{
public:
  bool testCollision(const Sphere & a, const Sphere & b, Collision * collision)const;
};
}
#pragma once
#include <Simulation/Collision/Collision.h>
#include <Simulation/Geometry/Primitives/Sphere.h>
#include <Simulation/Collision/Detection/CollisionTest/CollisionTest.h>

namespace IBDS{
struct SphereSphere{
  Sphere * _sphereA;
  Sphere * _sphereB;
public:
  bool testCollision(Collision & col);
};
}
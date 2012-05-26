#pragma once
#include <Simulation/Collision/Collision.h>
#include <Simulation/Geometry/Primitives/Plane.h>
#include <Simulation/Geometry/Primitives/Sphere.h>

namespace IBDS{
struct SpherePlane{
public:
  Sphere * _A;
  Plane * _B;
  bool testCollision(Collision * col)const;
};
}
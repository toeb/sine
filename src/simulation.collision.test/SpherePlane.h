#pragma once

#include <simulation.collision.test/CollisionTest.h>
#include <simulation.geometry/Plane.h>
#include <simulation.geometry/primitives/Sphere.h>

namespace nspace{
class SpherePlane : public CollisionTest{
public:
  SpherePlane():CollisionTest(Sphere::ClassType(),Plane::ClassType()){}
  bool testCollision(const ISimulationObject & a, const ISimulationObject & b, Collision * collision)const;
  bool testCollision(const Sphere & sphere, const Plane & plane, Collision * col)const;
};
}

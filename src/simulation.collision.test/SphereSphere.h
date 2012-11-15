#pragma once
#include <simulation.collision.test/CollisionTest.h>
#include <simulation.geometry/primitives/Sphere.h>

namespace nspace{
class SphereSphere : public CollisionTest{
public:  
  SphereSphere():CollisionTest(typeof(Sphere)->getId(),typeof(Sphere)->getId()){}
  bool testCollision(const ISimulationObject & a, const ISimulationObject & b, Collision * collision)const;
  bool testCollision(const Sphere & a, const Sphere & b, Collision * collision)const;
};


}
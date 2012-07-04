#pragma once
#include <Simulation/Collision/Detection/CollisionTest/CollisionTest.h>
#include <Simulation/Geometry/Primitives/Sphere.h>

namespace IBDS{
class SphereSphere : public CollisionTest{
public:  
  SphereSphere():CollisionTest(Sphere::type,Sphere::type){}
  bool testCollision(const ISimulationObject & a, const ISimulationObject & b, Collision * collision)const;
  bool testCollision(const Sphere & a, const Sphere & b, Collision * collision)const;
};


}
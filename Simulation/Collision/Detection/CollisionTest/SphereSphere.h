#pragma once
#include <Simulation/Collision/Detection/CollisionTest/CollisionTest.h>
#include <Simulation/Geometry/Primitives/Sphere.h>

namespace IBDS{
class SphereSphere : public CollisionTest{
public:
  
  const TypeId getTypeA()const;
  const TypeId getTypeB()const;
   bool testCollision(const ICollidable & a, const ICollidable & b, Collision * collision)const;
   bool testCollision(const Sphere & a, const Sphere & b, Collision * collision)const;
};


}
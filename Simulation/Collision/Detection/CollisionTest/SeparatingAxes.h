#pragma once

#include <Simulation/Collision/Detection/CollisionTest/CollisionTest.h>
#include <Simulation/Geometry/Polygon/Polygon.h>
namespace IBDS{
class SeparatingAxes : public CollisionTest{  
public:
  const TypeId getTypeA()const;
  const TypeId getTypeB()const;

  bool testCollision(const ICollidable & a, const ICollidable & b, Collision * collision)const;
};
}
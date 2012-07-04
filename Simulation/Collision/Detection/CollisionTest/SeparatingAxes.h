#pragma once

#include <Simulation/Collision/Detection/CollisionTest/CollisionTest.h>
#include <Simulation/Geometry/Polygon/Polygon.h>
namespace IBDS{
class SeparatingAxes : public CollisionTest{  
public:
  SeparatingAxes():CollisionTest(Polygon::type,Polygon::type){}

  bool testCollision(const ISimulationObject & a, const ISimulationObject & b, Collision * collision)const;
};
}
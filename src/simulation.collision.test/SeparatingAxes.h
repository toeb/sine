#pragma once

#include <simulation.collision.test/CollisionTest.h>
#include <simulation.geometry/polygon/Polygon.h>
namespace nspace{
class SeparatingAxes : public CollisionTest{  
public:
  SeparatingAxes():CollisionTest(Polygon::ClassType(),Polygon::ClassType()){}

  bool testCollision(const ISimulationObject & a, const ISimulationObject & b, Collision * collision)const;
};
}
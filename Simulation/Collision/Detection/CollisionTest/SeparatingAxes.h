#pragma once

#include <Simulation/Collision/Detection/CollisionTest/CollisionTest.h>
#include <Simulation/Collision/Collision.h>
#include <Simulation/Geometry/Polygon/Polygon.h>
namespace IBDS{
  class SeparatingAxes{
  
  public:
    Polygon * a;
    Polygon * b;
    bool testCollision(Collision & col);
  };
}
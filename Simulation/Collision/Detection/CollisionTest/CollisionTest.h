#pragma once
#include <Simulation/Collision/Collision.h>
namespace IBDS{
class CollisionTest{
private:
public:
  virtual bool testCollision(Collision * col)=0;
};
}
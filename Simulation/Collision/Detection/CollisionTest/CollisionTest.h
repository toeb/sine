#pragma once
#include <Simulation/Collision/Collision.h>
namespace IBDS{
class CollisionTest{
private:
public:
  virtual Collision* testCollision()const=0;
};
}
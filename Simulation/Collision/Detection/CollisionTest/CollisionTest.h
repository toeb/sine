#pragma once
#include <Simulation/Collision/Collision.h>
namespace IBDS{
class CollisionTest{
private:
public:
  
  virtual bool setCollidableA(Collidable* c)=0;
  virtual bool setCollidableB(Collidable* c)=0;

  virtual bool testCollision(Collision * col)=0;
};
}
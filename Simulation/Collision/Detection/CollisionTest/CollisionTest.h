#pragma once

#include <Simulation/Collision/Collision.h>
namespace IBDS{

class CollisionTest{
private:
public:
  virtual const TypeId getTypeA()const=0;
  virtual const TypeId getTypeB()const=0;
  
  virtual bool testCollision(const ISimulationObject &a, const ISimulationObject &b, Collision * collision=0)const=0;
  
};
}
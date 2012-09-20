#pragma once

#include <simulation.collision/Collision.h>
namespace nspace{

class CollisionTest{
private:
  const TypeId _typeA;
  const TypeId _typeB;
public:
  CollisionTest(const TypeId  a,const TypeId  b):_typeA(a),_typeB(b){}

  inline const TypeId getTypeA()const{return _typeA;};
  inline const TypeId getTypeB()const{return _typeB;};
  
  virtual bool testCollision(const ISimulationObject &a, const ISimulationObject &b, Collision * collision=0)const=0;
  
};
}
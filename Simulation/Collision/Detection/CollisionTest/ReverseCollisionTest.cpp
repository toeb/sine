#pragma once
#include "ReverseCollisionTest.h"

using namespace IBDS;
using namespace std;

ReverseCollisionTest::ReverseCollisionTest(CollisionTest & test):forwardTest(test){

}

const TypeId ReverseCollisionTest::getTypeA()const{
  return forwardTest.getTypeB();
}
const TypeId ReverseCollisionTest::getTypeB()const{
  return forwardTest.getTypeA();
}
bool ReverseCollisionTest::testCollision(const ICollidable & a, const ICollidable & b, Collision * collision)const{
  if(!collision) {
    return forwardTest.testCollision(b,a,0);
  }
  if(!forwardTest.testCollision(b,a,collision))return false;  
  Vector3D tmp;
  if(collision){
    collision->foreachContact([&tmp](Contact* contact){
      contact->normal = -contact->normal;
      tmp = contact->pA_wcs;
      contact->pA_wcs = contact->pB_wcs;
      contact->pB_wcs = tmp;
    });
  }
  return true;
}
  
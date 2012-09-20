#include "ReverseCollisionTest.h"

using namespace nspace;
using namespace std;

ReverseCollisionTest::ReverseCollisionTest(CollisionTest & test):CollisionTest(test.getTypeB(),test.getTypeA()),forwardTest(test){

}

bool ReverseCollisionTest::testCollision(const ISimulationObject & a, const ISimulationObject & b, Collision * collision)const{
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
  

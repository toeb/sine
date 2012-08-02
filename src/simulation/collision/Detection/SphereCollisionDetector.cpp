#include "SphereCollisionDetector.h"


using namespace std;
using namespace IBDS;


void SphereCollisionDetector::doCollisionDetection(Real t, Real h){
  foreachCombination([this](ICollidable * a, ICollidable * b){
    Collision * collision = new Collision(*a,*b);
    if(collisionTest.testCollision(*a,*b,collision)){
      addCollision(collision);
    }else{
      delete collision;
    }

  });
  
}

bool SphereCollisionDetector::acceptObject(ISim * collidable){
  if( !dynamic_cast<Sphere*>(&(collidable->getGeometry())))return false;
  return true;
}

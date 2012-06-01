#include "SphereCollisionDetector.h"


using namespace std;
using namespace IBDS;


void SphereCollisionDetector::detectCollisions(Real t, Real h){
  resetCollisions();
  
  foreachCombination([this](Collidable * a, Collidable * b){
    Collision * collision = new Collision(*a,*b);
    if(collisionTest.testCollision(*a,*b,collision)){
      addCollision(collision);
    }else{
      delete collision;
    }

  });
  
}

bool SphereCollisionDetector::acceptObject(Collidable * collidable){
  if( !dynamic_cast<Sphere*>(&(collidable->getGeometry())))return false;
  return true;
}

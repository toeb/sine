#include "SphereCollisionDetector.h"


using namespace std;
using namespace IBDS;


int SphereCollisionDetector::detectCollisions(Real t, Real h){
  resetCollisions();
  int cols = 0;
 
  foreachCombination([&cols,this](Collidable * a, Collidable * b){
    Collision * collision = new Collision(*a,*b);
    Sphere* sphereA = dynamic_cast<Sphere*>(&(a->getGeometry()));
    Sphere* sphereB = dynamic_cast<Sphere*>(&(b->getGeometry()));
    if(collisionTest.testCollision(*sphereA,*sphereB,collision)){
      addCollision(collision);
      cols++;
    }else{
      delete collision;
    }

  });
  
 
  return cols;
}

bool SphereCollisionDetector::acceptObject(Collidable * collidable){
  if( !dynamic_cast<Sphere*>(&(collidable->getGeometry())))return false;
  return true;
}

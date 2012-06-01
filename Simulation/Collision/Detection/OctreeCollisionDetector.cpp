#include "OctreeCollisionDetector.h"
#include <Simulation/Collision/Detection/Acceleration/Octree.h>

using namespace std;
using namespace IBDS;

void OctreeCollisionDetector::detectCollisions(Real t, Real h){
  resetCollisions();
  
  update();
  

  foreachCombination([this](Collidable* a, Collidable * b){
    Collision * collision = new Collision(*a,*b);
    Octree & aref = static_cast<Octree &>(*a);
    Octree & bref = static_cast<Octree &>(*b);
    if(collisionTest.testCollision(aref,bref,collision)){
      addCollision(collision);
    }else{
      delete collision;
    }
  });
  
}

bool OctreeCollisionDetector::acceptObject(Collidable * c){
  if(dynamic_cast<Octree*> (c))return true;
  return false;
}
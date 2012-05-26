#include "SphereCollisionDetector.h"


using namespace std;
using namespace IBDS;

#define GET_SPHERE(coll) dynamic_cast<Sphere*>( &( coll->getGeometricObject()))

int SphereCollisionDetector::detectCollisions(){
  resetCollisions();
  Collision collision;
  int cols = 0;
  vector<Collidable*> & collidables = objects();
  for(int i=0; i < collidables.size(); i++){
    collision.objectA = collidables.at(i);
    collisionTest._sphereA = GET_SPHERE(collision.objectA);
    for(int j=i+1; j < collidables.size(); j++){
      collision.objectB = collidables.at(j);
      collisionTest._sphereB = GET_SPHERE(collision.objectB);
      
      if(collisionTest.testCollision(collision)){
        addCollision(new Collision(collision));
        cols++;
      }
    }
  }
  return cols;
}

bool SphereCollisionDetector::acceptObject(Collidable * collidable){
  if( !dynamic_cast<Sphere*>(&(collidable->getGeometricObject())))return false;
  return true;
}

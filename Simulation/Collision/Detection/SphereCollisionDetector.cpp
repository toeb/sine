#include "SphereCollisionDetector.h"


using namespace std;
using namespace IBDS;

int SphereCollisionDetector::detectCollisions(){
  Collision collision;
  for(int i=0; i < _spheres.size(); i++){
    collisionTest._A = _spheres.at(i);
    for(int j=0; j < _spheres.size(); j++){
      if(i==j)continue;
      collisionTest._B = _spheres.at(j);
      if(collisionTest.testCollision(collision)){
        addCollision(new Collision(collision));
      }
    }
  }
  return 0;
}

void SphereCollisionDetector::onObjectAdded(Collidable * collidable){
  CollisionSphere * sphere  =dynamic_cast<CollisionSphere*>(collidable);
  if(sphere) _spheres.push_back(sphere);
}
void SphereCollisionDetector::onObjectRemoved(Collidable * collidable){
  CollisionSphere * sphere  =dynamic_cast<CollisionSphere*>(collidable);
  if(!sphere) return;
  auto it = find(_spheres.begin(), _spheres.end(), sphere);
  if(it==_spheres.end())return;
  _spheres.erase(it);
}


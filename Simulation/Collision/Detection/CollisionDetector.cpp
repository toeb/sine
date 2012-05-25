#include "CollisionDetector.h"

using namespace std;
using namespace IBDS;

CollisionDetector::CollisionDetector(){
}

const vector<Collision*>& CollisionDetector::getCollisions()const{
  return _collisions;
}

void CollisionDetector::resetCollisions(){
  for_each(_collisions.begin(), _collisions.end(), [](Collision* c){
    delete c;
  });
  _collisions.clear();
}

void CollisionDetector::addCollision(Collision * collision){
  _collisions.push_back(collision);
  collision->objectA->addCollision(collision);
  collision->objectB->addCollision(collision);

}
#include <simulation.collision/Collidable.h>
#include <algorithm>

using namespace std;
using namespace nspace;

Collidable::Collidable(ISimulationObject & collisionObject):
  _collisionObject(collisionObject),_collisionType(collisionObject.getType()->getId())
{
}

const TypeId Collidable::getCollisionType()const{
  return _collisionType ;
}

void Collidable::addCollision(Collision* col){
  _collisions.push_back(col);
}
void Collidable::reset(){
  resetCollidable();
  //do not delete collisions because this is done by collisiondetector
  _collisions.clear();
}
const std::vector<Collision*> & Collidable::collisions()const{
  return _collisions;
}

void Collidable::foreachCollision(function<void (Collision*)> f){
  for_each(_collisions.begin(), _collisions.end(), f);
}
bool Collidable::isColliding()const{
  return _collisions.size()!=0;
}
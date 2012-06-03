#include <Simulation/Collision/Collidable.h>
#include <algorithm>

using namespace std;
using namespace IBDS;

Collidable::Collidable(Geometry & o):_geometry(o){

}

const TypeId Collidable::getType()const{
  return _geometry.getType();
}

Geometry & Collidable::getGeometry()const{
  return _geometry;
}

void Collidable::addCollision(Collision* col){
  _collisions.push_back(col);
}
void Collidable::resetCollisions(){
  reset();
  _collisions.clear();
}
const std::vector<Collision*> & Collidable::getCollisions()const{
  return _collisions;
}

void Collidable::foreachCollision(function<void (Collision*)> f){
  for_each(_collisions.begin(), _collisions.end(), f);
}
bool Collidable::isColliding()const{
  return _collisions.size()!=0;
}
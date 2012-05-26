#include <Simulation/Collision/Collidable.h>
#include <algorithm>

using namespace std;
using namespace IBDS;

Collidable::Collidable(GeometricObject & o):_geometricObject(o){

}

GeometricObject & Collidable::getGeometricObject()const{
  return _geometricObject;
}

void Collidable::addCollision(Collision* col){
  _collisions.push_back(col);
}
void Collidable::resetCollisions(){
  _collisions.clear();
}
const std::vector<Collision*> & Collidable::getCollisions()const{
  return _collisions;
}

void Collidable::for_each_Collision(function<void (Collision*)> f){
  for_each(_collisions.begin(), _collisions.end(), f);
}
#include <Simulation/Collision/Collidable.h>
#include <algorithm>

using namespace std;
using namespace IBDS;

Collidable::Collidable(Geometry & o):_geometry(o){

}

Geometry & Collidable::getGeometry()const{
  return _geometry;
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
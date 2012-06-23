#include <Simulation/Collision/Collidable.h>
#include <algorithm>

using namespace std;
using namespace IBDS;

Collidable::Collidable(Geometry & geometry, RigidBody & rigidBody, double elasticity, double staticFriction, double dynamicFriction):
_geometry(geometry),
_rigidBody(&rigidBody),
_elasticityCoefficient(elasticity),
_staticFrictionCoefficient(staticFriction),
_dynamicFrictionCoefficient(dynamicFriction) {}

//Collidable::Collidable(Geometry & o):_geometry(o){}

Collidable::Collidable(Geometry & geometry, double elasticity, double staticFriction, double dynamicFriction):
_geometry(geometry),
_rigidBody(0),
_elasticityCoefficient(elasticity),
_staticFrictionCoefficient(staticFriction),
_dynamicFrictionCoefficient(dynamicFriction) {}


const TypeId Collidable::getCollisionType()const{
  return _geometry.getType();
}

Geometry & Collidable::getGeometry()const{
  return _geometry;
}

RigidBody * const Collidable::getRigidBody() const {
	return _rigidBody;
}


void Collidable::addCollision(Collision* col){
  _collisions.push_back(col);
}
void Collidable::reset(){
  resetCollidable();
  //do not delete collisions because this is done by collisiondetector
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


double Collidable::getElasticityCoefficient() const {
	return _elasticityCoefficient;
}

double Collidable::getStaticFrictionCoefficient() const {
	return _staticFrictionCoefficient;
}

double Collidable::getDynamicFrictionCoefficient() const {
	return _dynamicFrictionCoefficient;
}


void Collidable::setElasticityCoefficient(double e) {
	_elasticityCoefficient = e;
}

void Collidable::setStaticFrictionCoefficient(double s) {
	_staticFrictionCoefficient = s;
}

void Collidable::setDynamicFrictionCoefficient(double d) {
	_dynamicFrictionCoefficient = d;
}

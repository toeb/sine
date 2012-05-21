#include "Gravity.h"
using namespace IBDS;

Gravity::Gravity(void) {
	setGravity(Vector3D(0,-9.81,0));
}

Gravity::~Gravity(void)	{
}

Gravity::Gravity(Real g) {
	setGravity(Vector3D(0,-g,0));
}

Gravity::Gravity(const Vector3D & gravity){
  setGravity(gravity);
}

Real Gravity::getGravityMagnitude()const{
  return _amount;
}
void Gravity::setGravityMagnitude(Real amount){
  _amount = amount;
  calculateGravity();
}
void Gravity::setDirection(const Vector3D & dir){
  _direction.assign(dir);
  _direction.normalize();
  calculateGravity();
}
const Vector3D & Gravity::getDirection()const{
  return _direction;
}
void Gravity::calculateGravity(){
  _g = _direction*_amount;
}
void Gravity::setGravity(const Vector3D & gravity){
  setDirection(gravity);
  setGravityMagnitude(gravity.length());
  calculateGravity();
}
const Vector3D & Gravity::getGravity()const{
  return _g;
}

void Gravity::act (std::vector<DynamicBody*> & target, Real time) {
  _g = _direction * _amount;
	for (std::vector<DynamicBody*>::iterator it = target.begin(); it != target.end(); it++) {
		Vector3D amount = (*it)->getMass() * _g;
		(*it)->addExternalForce(amount);
	}
}

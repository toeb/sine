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

void Gravity::setGravity(const Vector3D & gravity){
  _g[0]= gravity[0];
  _g[1]= gravity[1];
  _g[2]= gravity[2];
}

void Gravity::act (std::vector<Body*> & target, Real time) {
	for (std::vector<Body*>::iterator it = target.begin(); it != target.end(); it++) {
		Vector3D amount = (*it)->getMass() * _g;
		(*it)->addExternalForce(amount);
	}
}

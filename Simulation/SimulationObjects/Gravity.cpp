#include "Gravity.h"
using namespace IBDS;

Gravity::Gravity(void) {
	_g = 9.81;
}

Gravity::~Gravity(void)	{
}

Gravity::Gravity(Real g) {
	_g = g;
}

void Gravity::act (std::vector<Body*> & target, Real time) {
	for (std::vector<Body*>::iterator it = target.begin(); it != target.end(); it++) {
		Real amount = (*it)->getMass() * _g;
		(*it)->addExternalForce(Vector3D(0,-amount,0));
	}
}

void Gravity::render() const {}
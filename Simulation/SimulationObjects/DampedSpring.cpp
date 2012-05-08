#include "DampedSpring.h"
using namespace IBDS;

DampedSpring::DampedSpring(void)
	{
	}

DampedSpring::~DampedSpring(void)
	{
	}

DampedSpring::DampedSpring(Connector *c1, Connector *c2, Real k_s, Real k_d, Real restLength) {
	_c1 = c1;
	_c2 = c2;
	_k_s = k_s;
	_k_d = k_d;
	_restLength = restLength;
}

void DampedSpring::act (std::vector<Body*> & target, Real time) {
	a = *(_c1->getPosition());
	b = *(_c2->getPosition());

	Vector3D v_a, v_b;
	v_a = *(_c1->getVelocity());
	v_b = *(_c2->getVelocity());

	Vector3D distVector;
	Vector3D springForce, dampForce, totalForce;
	Real dist;

	distVector = b - a;
	dist = distVector.length();

	springForce = _k_s * (dist - _restLength) * distVector * (1/dist);
	dampForce = (_k_d * (v_b - v_a) * distVector) * distVector * (1 / (dist * dist));
	totalForce = springForce + dampForce;

	_c1->addExternalForce(totalForce);
	_c2->addExternalForce(-totalForce);
}

void DampedSpring::render()  {
	// just draw a line between the 2 connectors
	MiniGL::drawVector(a,b,2,MiniGL::black);
}
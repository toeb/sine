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
  a = _c1->getWorldPosition();
  b = _c2->getWorldPosition();

  const Vector3D & v_a = _c1->getWorldVelocity();
  const Vector3D & v_b = _c2->getWorldVelocity();

	Vector3D normal;
	Vector3D springForce, dampForce, totalForce;
	Real dist;

	normal = b - a;
	dist = normal.length();
  normal = (1/dist)*normal;

	springForce = _k_s * (dist - _restLength) *normal;
	dampForce = (_k_d * (v_b - v_a) * normal) * normal ;
	totalForce = springForce + dampForce;

	_c1->addExternalForce(totalForce);
	_c2->addExternalForce(-totalForce);
}

void DampedSpring::render()  {
	// just draw a line between the 2 connectors
	MiniGL::drawVector(a,b,2,MiniGL::black);
}
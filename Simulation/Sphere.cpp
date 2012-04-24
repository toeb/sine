#include "Sphere.h"
using namespace IBDS;

Sphere::Sphere() {}

Sphere::~Sphere() {}

Sphere::Sphere(Real m, Real r) : _r(r) {
	RigidBody::setMass(m);

	Real scalarInertia = m*r*r*0.4; // 2/5*r²
	Matrix3x3 inertia;
	inertia = scalarInertia*inertia;
	RigidBody::setInertiaTensor(inertia);
}

void Sphere::render() const{
	MiniGL::drawSphere(&getPosition(),(float)_r,MiniGL::darkGray);
}
#include "Sphere.h"
using namespace IBDS;


DynamicSphere::~DynamicSphere() {}

DynamicSphere::DynamicSphere(Real m, Real r):Sphere(r){
	setMass(m);
  
	Real scalarInertia = m*r*r*0.4; // 2/5*r²
	Matrix3x3 inertia;
	inertia = scalarInertia*inertia;
	RigidBody::setInertiaTensor(inertia);
}

#include "Box.h"
using namespace IBDS;
using namespace std;
Box::Box() {}
Box::~Box() {}

Box::Box(Real m, Real x, Real y, Real z) : _x(x), _y(y), _z(z) {
  RigidBody::setMass(m);

  Matrix3x3 inertia;
  inertia(0,0) = y*y+z*z;
  inertia(1,1)= x*x+z*z;
  inertia(2,2)  = x*x+y*y;
  inertia = (1.0/12.0)*m* inertia;
  RigidBody::setInertiaTensor(inertia);
  }

Real Box::getXExtent()const{
  return _x;
}
Real Box::getYExtent()const{
  return _y;
}
Real Box::getZExtent()const{
  return _z;
}
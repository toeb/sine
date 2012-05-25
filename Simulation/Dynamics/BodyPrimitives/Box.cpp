#include "Box.h"
using namespace IBDS;
using namespace std;
DynamicBox::~DynamicBox() {}

DynamicBox::DynamicBox(Real m, Real x, Real y, Real z) :Hexahedron(x,y,z) {
  RigidBody::setMass(m);

  Matrix3x3 inertia;
  inertia(0,0) = y*y+z*z;
  inertia(1,1)= x*x+z*z;
  inertia(2,2)  = x*x+y*y;
  inertia = (1.0/12.0)*m* inertia;
  RigidBody::setInertiaTensor(inertia);
}


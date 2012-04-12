#include "RigidBody.h"
#include <Math/Quaternion.h>
using namespace IBDS;

const Vector3D & RigidBody::getAngularAcceleration()const {return _angularAcceleration;}
void RigidBody::setAngularAcceleration(const Vector3D & omegaDot){_angularAcceleration = omegaDot;}

const Vector3D & RigidBody::getAngularVelocity()const{return _angularVelocity;}
void RigidBody::setAngularVelocity(const Vector3D & omega){_angularVelocity = omega;}

const IBDS::Quaternion & RigidBody::getOrientation()const{return _orientation;}
void RigidBody::setOrientation(const IBDS::Quaternion & R){_orientation = R;}

void RigidBody::setInertiaTensor(const Matrix3x3 & inertia){_inertiaTensor=inertia;}
const Matrix3x3 &  RigidBody::getInertiaTensor()const{return _inertiaTensor;}

RigidBody* RigidBody::createSphere(Real m, Real r){
  RigidBody* sphere = new RigidBody();
  sphere->setMass(m);
  Real scalarInertia = m*r*r*0.4; // 2/5*r²
  Matrix3x3 inertia;
  inertia = scalarInertia*inertia;
  sphere->setInertiaTensor(inertia);
  return sphere;
}

RigidBody* RigidBody::createBox(Real mass, Real a, Real b, Real c){
  RigidBody* box = new RigidBody();
  box->setMass(m);
  Matrix3x3 inertia;
  inertia(0,0) = b*b+c*c;
  inertia(1,1)= a*a+c*c;
  inertia(2,2)  = a*a+b*b;
  inertia = (1.0/12.0)*m* inertia;
  box->setInertiaTensor(inertia);
  return box;
}

RigidBody* RigidBody::createCylinder(Real m, Real r, Real l){
  RigidBody* cylinder = new RigidBody();
  cylinder->setMass(m);
  Matrix3x3 inertia;
  inertia(0,0) = l*l/12+r*r/4;
  inertia(1,1) = l*l/12+r*r/4;
  inertia(2,2) = r*r/2;
  inertia = m*inertia;
  cylinder->setInertiaTensor(inertia);
  return cylinder;
}
#include "RigidBody.h"
#include <Math/Quaternion.h>
using namespace IBDS;



 void RigidBody::evaluate(const Real * state, Real * derivedState)
{
  Quaternion q;
  q[0] = state[0];
  q[1] = state[1];
  q[2] = state[2];
  q[3] = state[3];
  
  derivedState[0] = state[4];
  derivedState[1] = state[5];
  derivedState[2] = state[6];
  derivedState[3] = state[7];

  //really, really unoptimized code.
  Matrix3x3 R, RT;
  q.getMatrix3x3(R);
  q.getMatrix3x3T(RT);
  const Matrix3x3 & J = getInertiaTensor();
  Matrix3x3 J_inverted;
  J_inverted(0,0) = 1.0/J(0,0);
  J_inverted(1,1) = 1.0/J(1,1);
  J_inverted(2,2) = 1.0/J(2,2);
  Matrix3x3 J_wcs = R*J*RT;
  Matrix3x3 J_inverted_wcs = R*J_inverted*RT;
  Vector3D omegaDot = J_inverted_wcs *(_torqueAccumulator - _angularVelocity ^ (J_wcs*_angularVelocity));
  Quaternion omegaDotTilde;
  omegaDotTilde.w=0;
  omegaDotTilde.x=omegaDot[0];
  omegaDotTilde.y=omegaDot[1];
  omegaDotTilde.z=omegaDot[2];
  Quaternion qDot = 0.5*omegaDotTilde*_orientation;
  derivedState[4] = qDot[0];
  derivedState[5] = qDot[1];
  derivedState[6] = qDot[2];
  derivedState[7] = qDot[3];
  Particle::evaluate(state+8,derivedState+8);
}
void RigidBody::setState(const Real * state)
{
  _orientation[0] = state[0];
  _orientation[1] = state[1];
  _orientation[2] = state[2];
  _orientation[3] = state[3];

  Particle::setState(state+8);
}
 void RigidBody::getState(Real * state)const
{
  state[0] = _orientation[0];
  state[1] = _orientation[1];
  state[2] = _orientation[2];
  state[3] = _orientation[3];
  state[4] = _orientation[0];
  state[5] = _orientation[1];
  state[6] = _orientation[2];
  state[7] = _orientation[3];
  
  Particle::getState(state+8);
}

 int RigidBody::getStateDimension()const{
  return Particle::getStateDimension()+8;
}

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

RigidBody* RigidBody::createBox(Real m, Real a, Real b, Real c){
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
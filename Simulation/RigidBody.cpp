#include "RigidBody.h"
#include <Math/Quaternion.h>
using namespace IBDS;

RigidBody::RigidBody(){
  _R.x=0;
  _R.y=0;
  _R.z=0;
  _R.w=1;


}

void RigidBody::addExternalForceWCS(const IBDS::Vector3D & position, const IBDS::Vector3D & f){
  //_forceAccumulator
  Vector3D r = position - getPosition();
  // calculate torque
  Vector3D torque = f ^ r;
  // add force and torque to their accumulators
  _f+= f;
  _tau += torque;
}


void RigidBody::addExternalTorqueWCS(const IBDS::Vector3D & torque){
  _tau += torque;
}

/**
 * derivedState = (qDot, omegaDot, xDot, vDot)^T (dimension: 4+3+3+3 = 13)
 */
 void RigidBody::evaluate()
{
  if(_m==0){
    Vector3D nullVector(0,0,0);
    setAcceleration(nullVector);
    setVelocity(nullVector);
    setAngularAcceleration(nullVector);
    setAngularVelocity(nullVector);
    return;
  }
  //really, really unoptimized code.
  Matrix3x3 R, RT;
  _R.getMatrix3x3(R);
  _R.getMatrix3x3T(RT);

  Matrix3x3 J_inverted;
  J_inverted(0,0) = 1.0/_J(0,0);
  J_inverted(1,1) = 1.0/_J(1,1);
  J_inverted(2,2) = 1.0/_J(2,2);
  Matrix3x3 J_wcs = R*_J*RT;
  Matrix3x3 J_inverted_wcs = R*J_inverted*RT;
  _omegaDot = J_inverted_wcs *(_tau - (_omega ^ (J_wcs*_omega)));
  _rDotDot = _f * (1/_m);
  
}

 const Vector3D & RigidBody::getForce()const{
   return _f;
 }
void RigidBody::getDerivedState(Real * xDot)const{
  Quaternion omegaTilde;
  omegaTilde.w=0;
  omegaTilde.x=_omega[0];
  omegaTilde.y=_omega[1];
  omegaTilde.z=_omega[2];
  Quaternion qDot = 0.5*omegaTilde*_R;
  
  xDot[0] = _rDot[0];
  xDot[1] = _rDot[1];
  xDot[2] = _rDot[2];
  xDot[3] = _rDotDot[0];
  xDot[4] = _rDotDot[1];
  xDot[5] = _rDotDot[2];
  xDot[6] = qDot[0];
  xDot[7] = qDot[1];
  xDot[8] = qDot[2];
  xDot[9] = qDot[3];
  xDot[10]= _omegaDot[0];
  xDot[11]= _omegaDot[1];
  xDot[12]= _omegaDot[2]; 
}
/**
 * state = (q, omega, x, v)^T (dimension: 4+3+3+3 = 13)
 */
void RigidBody::setState(const Real * state)
{
  _r[0]     = state[0];
  _rDot[0]  = state[1];
  _r[1]     = state[2];
  _rDot[1]  = state[3];
  _r[2]     = state[4];
  _rDot[2]  = state[5];

  _R[0] = state[6];
  _R[1] = state[7];
  _R[2] = state[8];
  _R[3] = state[9];

  _omega[0] = state[10];
  _omega[1] = state[11];
  _omega[2] = state[12];
}
/**
 * state = (q, omega, x, v)^T (dimension: 4+3+3+3 = 13)
 */
 void RigidBody::getState(Real * state)const
{
  state[0]= _r[0]     ;
  state[1]= _rDot[0]  ;
  state[2]= _r[1]     ;
  state[3]= _rDot[1]  ;
  state[4]= _r[2]     ;
  state[5]= _rDot[2]  ;

  state[6]=_R[0];
  state[7]=_R[1];
  state[8]=_R[2];
  state[9]=_R[3];

  state[10]=_omega[0] ;
  state[11]=_omega[1] ;
  state[12]=_omega[2] ;
}

 int RigidBody::getStateDimension()const{
  return 13;
}

const Vector3D & RigidBody::getPosition()const {return _r;}
void RigidBody::setPosition(const Vector3D & r){_r = r;}

const Vector3D & RigidBody::getVelocity()const {return _rDot;}
void RigidBody::setVelocity(const Vector3D & rDot){_rDot = rDot;}

const Vector3D & RigidBody::getAcceleration()const {return _rDotDot;}
void RigidBody::setAcceleration(const Vector3D & rDotDot){_rDotDot = rDotDot;}

const Vector3D & RigidBody::getAngularAcceleration()const {return _omegaDot;}
void RigidBody::setAngularAcceleration(const Vector3D & omegaDot){_omegaDot = omegaDot;}

const Vector3D & RigidBody::getAngularVelocity()const{return _omega;}
void RigidBody::setAngularVelocity(const Vector3D & omega){_omega = omega;}

const IBDS::Quaternion & RigidBody::getOrientation()const{return _R;}
void RigidBody::setOrientation(const IBDS::Quaternion & R){_R = R;}

Real RigidBody::getMass()const{return _m;}
void RigidBody::setMass(Real mass){ _m = mass;}

void RigidBody::setInertiaTensor(const Matrix3x3 & inertia){_J=inertia;}
const Matrix3x3 &  RigidBody::getInertiaTensor()const{return _J;}

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
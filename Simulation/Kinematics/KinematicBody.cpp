#include "KinematicBody.h"

using namespace IBDS;

void KinematicBody::addVelocity(const Vector3D & v){
  Vector3D::add(_v,v,_v);
}
void KinematicBody::addAngularVelocity(const Vector3D & dOmega){
  Vector3D::add(_omega,dOmega,_omega);
}
void KinematicBody::setMovementToZero(){  
  setVelocity(Vector3D::Zero());
  setAcceleration(Vector3D::Zero());
  setAngularVelocity(Vector3D::Zero());
  setAngularAcceleration(Vector3D::Zero());
}
void KinematicBody::setZero(){
  setPosition(Vector3D::Zero());
  setOrientation(Quaternion::zeroRotation());
  setMovementToZero();
}

KinematicBody::KinematicBody(){
 setZero();
}

KinematicBody::~KinematicBody() {
}

void KinematicBody::getDerivedState(Real * xDot)const{
  Quaternion qDot;
  qDot.w=0;
  qDot.x=_omega[0];
  qDot.y=_omega[1];
  qDot.z=_omega[2];
  
  qDot = 0.5*qDot*getOrientation();

  _v.copyTo(&(xDot[0]));
  _a.copyTo(&(xDot[3]));
  qDot.copyTo(&(xDot[6]));
  _omegaDot.copyTo(&(xDot[10]));
}

void KinematicBody::evaluate()
{

}

 /**
 * state = (x1,v1, x2,v2, x3,v3, q1,q2,q3,q4, omega1,omega2,omega3). dimension: 2*3+4+3=13
 */

void KinematicBody::setState(const Real * state)
{
  _p.assign(&state[0]);
  _v.assign(&(state[3]));
  
  _orientation.assign(&(state[6]));
  _orientation.normalize();
  
  _omega.assign(&(state[10]));
}

 /**
 * state = (x1,v1, x2,v2, x3,v3, q1,q2,q3,q4, omega1,omega2,omega3). dimension: 2*3+4+3=13
 */
 void KinematicBody::getState(Real * state)const
{
  _p.copyTo(&(state[0]));
  _v.copyTo(&(state[3]));
  _orientation.copyTo(&(state[6]));
  _omega.copyTo(&(state[10]));
}

 int KinematicBody::getStateDimension()const{
  return 13;
}


const Vector3D & KinematicBody::getVelocity()const {return _v;}
void KinematicBody::setVelocity(const Vector3D & rDot){_v= rDot;}

const Vector3D & KinematicBody::getAngularAcceleration()const {
  return _omegaDot;
}
void KinematicBody::setAngularAcceleration(const Vector3D & omegaDot){
  _omegaDot = omegaDot;
}
const Vector3D & KinematicBody::getAcceleration()const{
  return  _a;
}
void KinematicBody::setAcceleration(const Vector3D & a_wcs){
  _a = a_wcs;
}

const Vector3D & KinematicBody::getAngularVelocity()const{return _omega;}
void KinematicBody::setAngularVelocity(const Vector3D & omega){_omega = omega;}


  


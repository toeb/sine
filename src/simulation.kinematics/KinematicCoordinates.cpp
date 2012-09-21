#include "KinematicCoordinates.h"

using namespace nspace;

void KinematicBody::setMovementToZero(){  
  velocity().setZero();
  acceleration().setZero();
  angularVelocity().setZero();
  angularAcceleration().setZero();
}
void KinematicBody::setZero(){
  position().setZero();
  orientation() = Quaternion::Identity();
  setMovementToZero();
}
KinematicBody::KinematicBody():
StatefulObject(13,2),
velocity(& (Vector3D)Vector3D::Zero()), // casting to vector 3d is needed because of eigen library
acceleration(& (Vector3D)Vector3D::Zero()),
angularAcceleration(& (Vector3D)Vector3D::Zero()),
angularVelocity(& (Vector3D)Vector3D::Zero())
{
 setZero();
}

KinematicBody::~KinematicBody() {
}

Quaternion qOmega(const Quaternion & orientation, const Vector3D & omega){
  Quaternion result;

  //return Quaternion::zeroRotation();
/* Matrix4x3 Q =Quaternion::Q(orientation); 
 Quaternion result;
 Quaternion::multiply(0.5*Q, omega,result);
 */
 return result;
}

inline void transformAngularVelocity(Quaternion & qDot, const Vector3D & omega, const Quaternion & q){
  qDot.w() = 0.0;
  qDot.x()=omega.x();
  qDot.y()=omega.y();
  qDot.z()=omega.z();
  qDot = 0.5*(q*qDot);
}

Quaternion qOmegaDot(const Quaternion & orientation, const Vector3D & omega, const Vector3D & omegaDot){
/*  Matrix4x3 Q =Quaternion::Q(orientation); 
  Matrix4x3 Qdot = Quaternion::Q(qOmega(orientation,omega));

  Quaternion a;
  Quaternion::multiply(0.5*Qdot, omega,a);
  Quaternion b;
  Quaternion::multiply(0.5*Q, omegaDot,b);*/
  Quaternion result;// = a+b;
  return result;
}
void KinematicBody::notifyStateNeeded(){
  Real * x = state().stateVector(0);
  Real * xDot = state().stateVector(1);

  position().copyTo(x);
  velocity().copyTo(x+3);
  orientation().copyTo(x+6);
  angularVelocity().copyTo(x+10);

  velocity().copyTo(xDot);
  acceleration().copyTo(xDot+3);
  Quaternion qDot;
  transformAngularVelocity(qDot,angularVelocity(),orientation());
  qDot.copyTo(xDot+6);
  angularAcceleration().copyTo(xDot+10);
}

 /**
 * state = (x1,v1, x2,v2, x3,v3, q1,q2,q3,q4, omega1,omega2,omega3). dimension: 2*3+4+3=13
 */

void KinematicBody::notifyStateChanged()
{ 
  Real * x = state().stateVector(0);
  //Real * xDot = state().stateVector(0);

  position().assign(x);
  velocity().assign(x+3);
  orientation().assign(x+6);
  angularVelocity().assign(x+10);

  /*velocity().assign(xDot);
  acceleration().assign(xDot+3);
  Quaternion qDot;
  transformAngularVelocity(qDot,angularVelocity(),orientation());
  qDot.assign(x+6);
  angularAcceleration().assign(xDot+10);*/
}



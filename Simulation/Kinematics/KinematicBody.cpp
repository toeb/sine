#include "KinematicBody.h"

using namespace IBDS;

void KinematicBody::setMovementToZero(){  
  velocity().setZero();
  acceleration().setZero();
  angularVelocity().setZero();
  angularAcceleration().setZero();
}
void KinematicBody::setZero(){
  position().setZero();
  orientation() = Quaternion::zeroRotation();
  setMovementToZero();
}

KinematicBody::KinematicBody():
velocity(&Vector3D::Zero()),
acceleration(&Vector3D::Zero()),
angularAcceleration(&Vector3D::Zero()),
angularVelocity(&Vector3D::Zero())
{
 setZero();
}

KinematicBody::~KinematicBody() {
}

void KinematicBody::getDerivedState(Real * xDot)const{
  // calculate angularvelocity in quaternion form
  Quaternion qDot;
  qDot.w=0;
  qDot.x=angularVelocity()[0];
  qDot.y=angularVelocity()[1];
  qDot.z=angularVelocity()[2];
  
  qDot = 0.5*qDot*orientation();

  //copy derived state into the corresponding array

  velocity().copyTo(&(xDot[0]));
  acceleration().copyTo(&(xDot[3]));
  qDot.copyTo(&(xDot[6]));
  angularAcceleration().copyTo(&(xDot[10]));
  Real vals[13];
  for(int i= 0; i < 13; i++){
    vals[i] = xDot[i];
  }
}


 /**
 * state = (x1,v1, x2,v2, x3,v3, q1,q2,q3,q4, omega1,omega2,omega3). dimension: 2*3+4+3=13
 */

void KinematicBody::setState(const Real * state)
{
  position().assign(&state[0]);
  velocity().assign(&(state[3]));
  orientation().assign(&(state[6]));
  orientation().normalize();
  angularVelocity().assign(&(state[10]));
}

 /**
 * state = (x1,v1, x2,v2, x3,v3, q1,q2,q3,q4, omega1,omega2,omega3). dimension: 2*3+4+3=13
 */
 void KinematicBody::getState(Real * state)const
{
  position().copyTo(&(state[0]));
  velocity().copyTo(&(state[3]));
  orientation().copyTo(&(state[6]));
  angularVelocity().copyTo(&(state[10]));
}

 int KinematicBody::getStateDimension()const{
  return 13;
}




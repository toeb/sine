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

Quaternion qOmega(const Quaternion & orientation, const Vector3D & omega){
  //return Quaternion::zeroRotation();
 Matrix4x3 Q =Quaternion::Q(orientation); 
 Quaternion result;
 Quaternion::multiply(0.5*Q, omega,result);

 return result;
}

Quaternion qOmegaDot(const Quaternion & orientation, const Vector3D & omega, const Vector3D & omegaDot){
  Matrix4x3 Q =Quaternion::Q(orientation); 
  Matrix4x3 Qdot = Quaternion::Q(qOmega(orientation,omega));

  Quaternion a;
  Quaternion::multiply(0.5*Qdot, omega,a);
  Quaternion b;
  Quaternion::multiply(0.5*Q, omegaDot,b);
  Quaternion result = a+b;
  return result;
}
void KinematicBody::exportDerivedState(IState & xDot)const{
  xDot(0,0) =  velocity()(0);
  xDot(1,0) =  velocity()(1);
  xDot(2,0) =  velocity()(2);

  xDot(3,0) = acceleration()(0);
  xDot(4,0) = acceleration()(1);
  xDot(5,0) = acceleration()(2);

  Quaternion omegaTilde;
  omegaTilde(0)=0;
  omegaTilde(1)=angularVelocity()(0);
  omegaTilde(2)=angularVelocity()(1);
  omegaTilde(3)=angularVelocity()(2);

  Quaternion qDot =0.5*orientation()*omegaTilde;

  xDot(6,0) = qDot(0);
  xDot(7,0) = qDot(1);
  xDot(8,0) = qDot(2);
  xDot(9,0) = qDot(3);

  xDot(10,0) = angularAcceleration()(0);
  xDot(11,0) = angularAcceleration()(1);
  xDot(12,0) = angularAcceleration()(2);
  /*// calculate angularvelocity in quaternion form
  xDot(0,0) = velocity()(0);
  xDot(1,0) = velocity()(1);
  xDot(2,0) = velocity()(2);
  
  xDot(0,1) = acceleration()(0);
  xDot(1,1) = acceleration()(1);
  xDot(2,1) = acceleration()(2);
  
  Quaternion qDot = qOmega(orientation(),angularVelocity());
  xDot(3,0) = qDot[0];
  xDot(4,0) = qDot[1];
  xDot(5,0) = qDot[2];
  xDot(6,0) = qDot[3];

  Quaternion qDotDot = qOmegaDot(orientation(), angularVelocity(), angularAcceleration());  
  xDot(3,1) = qDot[0];
  xDot(4,1) = qDot[1];
  xDot(5,1) = qDot[2];
  xDot(6,1) = qDot[3];

  //copy derived state into the corresponding array
  /*
  copyTo(velocity(),&(xDot[0]));
  copyTo(acceleration(),&(xDot[3]));
  qDot.copyTo(&(xDot[6]));
  copyTo(angularAcceleration(),&(xDot[10]));
  Real vals[13];
  for(int i= 0; i < 13; i++){
    vals[i] = xDot[i];
  }*/
}

 /**
 * state = (x1,v1, x2,v2, x3,v3, q1,q2,q3,q4, omega1,omega2,omega3). dimension: 2*3+4+3=13
 */

void KinematicBody::importState(const IState & state)
{
  position()(0)            =   state(0,0)    ;
  position()(1)            =    state(1,0) ;
  position()(2)            =    state(2,0) ;

  velocity()(0)           =    state(3,0)  ;
  velocity()(1)           =    state(4,0)  ;
  velocity()(2)           =    state(5,0)  ;

  orientation()(0)         =    state(6,0) ;
  orientation()(1)         =    state(7,0) ;
  orientation()(2)         =    state(8,0) ;
  orientation()(3)        =    state(9,0)  ;

  angularVelocity()(0)     =    state(10,0);
  angularVelocity()(1)     =    state(11,0);
  angularVelocity()(2)     =    state(12,0);
  /*
  position()(0) = state(0,0);
  position()(1) = state(1,0);
  position()(2) = state(2,0);
                  
  velocity()(0) = state(0,1);
  velocity()(1) = state(1,1);
  velocity()(2) = state(2,1);
                             
  orientation()[0] = state(3,0);
  orientation()[1] = state(4,0);
  orientation()[2] = state(5,0);
  orientation()[3] = state(6,0);

  orientation().normalize();

  Quaternion qDot;
  qDot[0] = state(3,1);
  qDot[1] = state(4,1);
  qDot[2] = state(5,1);
  qDot[3] = state(6,1);

  //transform back;
  Vector3D omega = orientation().transformAngularVelocity(qDot);

  angularVelocity() = omega;
  /*
	assign(&state[0],position());
  orientation().assign(&(state[6]));
  orientation().normalize();
	assign(&state[10],angularVelocity());*/
}

 /**
 * state = (x1,v1, x2,v2, x3,v3, q1,q2,q3,q4, omega1,omega2,omega3). dimension: 2*3+4+3=13
 */
 void KinematicBody::exportState(IState & state)const
{
  state(0,0) = position()(0);
  state(1,0) = position()(1);
  state(2,0) = position()(2);

  state(3,0) = velocity()(0);
  state(4,0) = velocity()(1);
  state(5,0) = velocity()(2);

  state(6,0) = orientation()(0);
  state(7,0) = orientation()(1);
  state(8,0) = orientation()(2);
  state(9,0) = orientation()(3);


  state(10,0) = angularVelocity()(0);
  state(11,0) = angularVelocity()(1);
  state(12,0) = angularVelocity()(2);
  /*
  state(0,0) = position()(0);
  state(1,0) = position()(1);
  state(2,0) = position()(2);
  
  state(0,1) = velocity()(0);
  state(1,1) = velocity()(1);
  state(2,1) = velocity()(2);
  
  state(3,0) = orientation()[0];
  state(4,0) = orientation()[1];
  state(5,0) = orientation()[2];
  state(6,0) = orientation()[3];

  Quaternion qDot = qOmega(orientation(),angularVelocity());
  
  state(3,1) = qDot[0];
  state(4,1) = qDot[1];
  state(5,1) = qDot[2];
  state(6,1) = qDot[3];
  */
  /*
  copyTo(position(), &(state[0]));
  copyTo(velocity(), &(state[3]));
  copyTo(angularVelocity(), &(state[10]));
  orientation().copyTo(&(state[6]));
*/
 }

unsigned int KinematicBody::stateDimension()const{
  return 13U;
}

unsigned int KinematicBody::availableDerivatives()const{
  return 1U;
}





/*#include "KinematicBody.h"

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



void KinematicBody::setState(const Real * state)
{
  position().assign(&state[0]);
  velocity().assign(&(state[3]));
  orientation().assign(&(state[6]));
  orientation().normalize();
  angularVelocity().assign(&(state[10]));
}


 void KinematicBody::getState(Real * state)const
{
  position().copyTo(&(state[0]));
  velocity().copyTo(&(state[3]));
  orientation().copyTo(&(state[6]));
  angularVelocity().copyTo(&(state[10]));
}

 int KinematicBody::getStateDimension()const{
  return 13;
}*/
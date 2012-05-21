#include "KinematicBody.h"

using namespace IBDS;

void KinematicBody::worldToObjectCoordinates(const Vector3D & r_wcs, Vector3D & r_ocs)const{
    Vector3D r = r_wcs - getPosition();
    const Matrix3x3 & RT = getTransposedRotationMatrix();
    r_ocs.assign(RT*r);
}

void KinematicBody::objectToWorldCoordinates(const Vector3D & r_ocs, Vector3D & r_wcs)const{
  const Matrix3x3 & R = getRotationMatrix();
  r_wcs.assign(getPosition() + R* r_ocs);
}
void KinematicBody::setMovementToZero(){  
  setVelocity(Vector3D::Zero());
  setAcceleration(Vector3D::Zero());
  setAngularVelocity(Vector3D::Zero());
  setAngularAcceleration(Vector3D::Zero());
}
void KinematicBody::setZero(){
  setPosition(Vector3D::Zero());
  _q.w=1;
  _q.x=0;
  _q.y=0;
  _q.z=0;
  setMovementToZero();
}

KinematicBody::KinematicBody(){
 setZero();
}

KinematicBody::~KinematicBody() {
}

 /**
 * derivedState = (v1,a1, v2,a2, v3,a3, qDot1,qDot3,qDot2,qDot4, omegaDot1,omegaDot2,omegaDot3) (dimension: 2*3+4+3=13)
 */
void KinematicBody::getDerivedState(Real * xDot)const{
  Quaternion omegaTilde;
  omegaTilde.w=0;
  omegaTilde.x=_omega[0];
  omegaTilde.y=_omega[1];
  omegaTilde.z=_omega[2];
  Quaternion qDot = 0.5*omegaTilde*_q;


  const Vector3D & a_wcs = getAcceleration();

  xDot[0] = _xDot[0];
  xDot[1] = a_wcs[0];
  xDot[2] = _xDot[1];
  xDot[3] = a_wcs[1];
  xDot[4] = _xDot[2];
  xDot[5] = a_wcs[2];

  xDot[6] = qDot[0];
  xDot[7] = qDot[1];
  xDot[8] = qDot[2];
  xDot[9] = qDot[3];
  xDot[10]= _omegaDot[0];
  xDot[11]= _omegaDot[1];
  xDot[12]= _omegaDot[2]; 
}

void KinematicBody::evaluate()
{

}

 /**
 * state = (x1,v1, x2,v2, x3,v3, q1,q2,q3,q4, omega1,omega2,omega3). dimension: 2*3+4+3=13
 */
void KinematicBody::setState(const Real * state)
{
  _x[0]     = state[0];
  _xDot[0]  = state[1];
  _x[1]     = state[2];
  _xDot[1]  = state[3];
  _x[2]     = state[4];
  _xDot[2]  = state[5];

  _q[0] = state[6];
  _q[1] = state[7];
  _q[2] = state[8];
  _q[3] = state[9];
  
  // normalise orientation .
  _q.normalize();

  _omega[0] = state[10];
  _omega[1] = state[11];
  _omega[2] = state[12];
}

 /**
 * state = (x1,v1, x2,v2, x3,v3, q1,q2,q3,q4, omega1,omega2,omega3). dimension: 2*3+4+3=13
 */
 void KinematicBody::getState(Real * state)const
{
  state[0]= _x[0]     ;
  state[1]= _xDot[0]  ;
  state[2]= _x[1]     ;
  state[3]= _xDot[1]  ;
  state[4]= _x[2]     ;
  state[5]= _xDot[2]  ;
 
  state[6]=_q[0];
  state[7]=_q[1];
  state[8]=_q[2];
  state[9]=_q[3];

  state[10]=_omega[0] ;
  state[11]=_omega[1] ;
  state[12]=_omega[2] ;
}

 int KinematicBody::getStateDimension()const{
  return 13;
}


const Vector3D & KinematicBody::getPosition()const {return _x;}
void KinematicBody::setPosition(const Vector3D & r){_x = r;}

const Vector3D & KinematicBody::getVelocity()const {return _xDot;}
void KinematicBody::setVelocity(const Vector3D & rDot){_xDot = rDot;}

const Vector3D & KinematicBody::getAngularAcceleration()const {
  return _omegaDot;
}
void KinematicBody::setAngularAcceleration(const Vector3D & omegaDot){
  _omegaDot = omegaDot;
}
const Vector3D & KinematicBody::getAcceleration()const{
  return  _xDotDot;
}
void KinematicBody::setAcceleration(const Vector3D & a_wcs){
  _xDotDot = a_wcs;
}

const Vector3D & KinematicBody::getAngularVelocity()const{return _omega;}
void KinematicBody::setAngularVelocity(const Vector3D & omega){_omega = omega;}

const IBDS::Quaternion & KinematicBody::getOrientation()const {return _q;}
void KinematicBody::setOrientation(const IBDS::Quaternion & R){_q = R;}

const Matrix3x3 & KinematicBody::getRotationMatrix()const{
  return _R;
}
const Matrix3x3 & KinematicBody::getTransposedRotationMatrix()const{
  return _RT;
}
void KinematicBody::calculateRotationMatrices(){
  const Quaternion & q = getOrientation();
  q.getMatrix3x3(_R);
  Matrix3x3::transpose(_R,_RT);
}


  


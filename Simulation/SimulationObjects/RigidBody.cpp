#include "RigidBody.h"
#include <Math/Quaternion.h>
#include <Simulation/SimulationObjects/Box.h>
#include <Math/SimMath.h>
using namespace IBDS;

Vector3D & RigidBody::worldToObjectCoordinates(const Vector3D & r_wcs)const{
    Vector3D r_ocs = r_wcs - getPosition();
    Matrix3x3 & RT = getOrientation().createTransposedRotationMatrix();
    r_ocs=RT*r_ocs;
    return r_ocs.copy();
}

Vector3D & RigidBody::objectToWorldCoordinates(const Vector3D & r_ocs)const{
  Matrix3x3 & R = getOrientation().createRotationMatrix();
  Vector3D r_wcs= getPosition() + R* r_ocs;
  return r_wcs.copy();
}

RigidBody::RigidBody(){
  _q.w=1;
  _q.x=0;
  _q.y=0;
  _q.z=0;
}

RigidBody::~RigidBody() {
	}

 /**
 * derivedState = (v1,a1, v2,a2, v3,a3, qDot1,qDot3,qDot2,qDot4, omegaDot1,omegaDot2,omegaDot3) (dimension: 2*3+4+3=13)
 */
void RigidBody::getDerivedState(Real * xDot)const{
  Quaternion omegaTilde;
  omegaTilde.w=0;
  omegaTilde.x=_omega[0];
  omegaTilde.y=_omega[1];
  omegaTilde.z=_omega[2];
  Quaternion qDot = 0.5*omegaTilde*_q;
  
 /* xDot[0] = _xDot[0];
  xDot[1] = _xDot[1];
  xDot[2] = _xDot[2];
  xDot[3] = _xDotDot[0];
  xDot[4] = _xDotDot[1];
  xDot[5] = _xDotDot[2];*/

  xDot[0] = _xDot[0];
  xDot[1] = _xDotDot[0];
  xDot[2] = _xDot[1];
  xDot[3] = _xDotDot[1];
  xDot[4] = _xDot[2];
  xDot[5] = _xDotDot[2];

  xDot[6] = qDot[0];
  xDot[7] = qDot[1];
  xDot[8] = qDot[2];
  xDot[9] = qDot[3];
  xDot[10]= _omegaDot[0];
  xDot[11]= _omegaDot[1];
  xDot[12]= _omegaDot[2]; 
}

void RigidBody::evaluate()
{
  if(_m==0){
    Vector3D nullVector(0,0,0);
    setAcceleration(nullVector);
    /*setVelocity(nullVector);
    setAngularAcceleration(nullVector);*/
    setAngularVelocity(nullVector);
    return;
  }
  //really, really unoptimized code.
  Matrix3x3 R, RT;
  _q.getMatrix3x3(R);
  _q.getMatrix3x3T(RT);

 /* Matrix3x3 J_inverted;
  J_inverted(0,0) = 1.0/_J(0,0);
  J_inverted(1,1) = 1.0/_J(1,1);
  J_inverted(2,2) = 1.0/_J(2,2);*/
  Matrix3x3 J_inverted = getInvertedInertiaTensor();

  Matrix3x3 J_wcs = R*_J*RT;
  Matrix3x3 J_inverted_wcs = R*J_inverted*RT;
  _omegaDot = J_inverted_wcs *(_tau - (_omega ^ (J_wcs*_omega)));

  _xDotDot = _f * (1/_m);
  
}
 /**
 * state = (x1,v1, x2,v2, x3,v3, q1,q2,q3,q4, omega1,omega2,omega3). dimension: 2*3+4+3=13
 */
void RigidBody::setState(const Real * state)
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
 void RigidBody::getState(Real * state)const
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

 int RigidBody::getStateDimension()const{
  return 13;
}

void RigidBody::addExternalForce(const IBDS::Vector3D & position, const IBDS::Vector3D & f){
  //_forceAccumulator
  Vector3D r = position - getPosition();
  // calculate torque
  Vector3D torque = r ^ f; 
  // add force and torque to their accumulators
  _f+= f;
  _tau += torque;
}

void RigidBody::addExternalForce(const IBDS::Vector3D & f){
  _f+= f;
}

void RigidBody::resetForce() {
	_f = Vector3D();
	_tau = Vector3D();
}


void RigidBody::addExternalTorque(const IBDS::Vector3D & torque){
  _tau += torque;
}

 const Vector3D & RigidBody::getForce()const{
   return _f;
 }

const Vector3D & RigidBody::getPosition()const {return _x;}
void RigidBody::setPosition(const Vector3D & r){_x = r;}

const Vector3D & RigidBody::getVelocity()const {return _xDot;}
void RigidBody::setVelocity(const Vector3D & rDot){_xDot = rDot;}

const Vector3D & RigidBody::getAcceleration()const {return _xDotDot;}
void RigidBody::setAcceleration(const Vector3D & rDotDot){_xDotDot = rDotDot;}

const Vector3D & RigidBody::getAngularAcceleration()const {return _omegaDot;}
void RigidBody::setAngularAcceleration(const Vector3D & omegaDot){_omegaDot = omegaDot;}

const Vector3D & RigidBody::getAngularVelocity()const{return _omega;}
void RigidBody::setAngularVelocity(const Vector3D & omega){_omega = omega;}

const IBDS::Quaternion & RigidBody::getOrientation()const {return _q;}
void RigidBody::setOrientation(const IBDS::Quaternion & R){_q = R;}

Real RigidBody::getMass()const{return _m;}
void RigidBody::setMass(Real mass){ _m = mass;}

void RigidBody::setInertiaTensor(const Matrix3x3 & inertia){_J=inertia;}
const Matrix3x3 &  RigidBody::getInertiaTensor()const{return _J;}

const Matrix3x3 & RigidBody::getInvertedInertiaTensor() const {
	Matrix3x3 J_inverted;
	J_inverted(0,0) = 1.0/_J(0,0);
	J_inverted(1,1) = 1.0/_J(1,1);
	J_inverted(2,2) = 1.0/_J(2,2);
	return *(new Matrix3x3(J_inverted));
}

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
  /*RigidBody* box = new RigidBody();
  box->setMass(m);
  Matrix3x3 inertia;
  inertia(0,0) = b*b+c*c;
  inertia(1,1)= a*a+c*c;
  inertia(2,2)  = a*a+b*b;
  inertia = (1.0/12.0)*m* inertia;
  box->setInertiaTensor(inertia);
  return box;*/
	return new Box(m,a,b,c);
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

const Matrix3x3 &  RigidBody::calculateK(const Vector3D & a, const Vector3D & b)const{
  Real m = getMass();
  if (m == 0) return Matrix3x3::Zero();

  const Matrix3x3 & E_3 = Matrix3x3::Identity();

	Matrix3x3 r_a_star = SimMath::crossProductMatrix(a);
  Matrix3x3 r_b_star = SimMath::crossProductMatrix(b);
  
	Matrix3x3 R, RT;

	Quaternion q = getOrientation();
	q.getMatrix3x3(R);
	q.getMatrix3x3T(RT);
	
  const Matrix3x3 & J_inv = getInvertedInertiaTensor();
	Matrix3x3 J_inv_wcs = R*J_inv*RT;
  
  Matrix3x3 K = (1/m)*E_3 - r_a_star * J_inv_wcs * r_b_star;

	return *(new Matrix3x3(K));
};
  


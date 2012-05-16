#include "RigidBody.h"
#include <Math/Quaternion.h>
#include <Simulation/Dynamics/BodyPrimitives/Box.h>
#include <Math/SimMath.h>

using namespace IBDS;

void RigidBody::worldToObjectCoordinates(const Vector3D & r_wcs, Vector3D & r_ocs)const{
    Vector3D r = r_wcs - getPosition();
    const Matrix3x3 & RT = getTransposedRotationMatrix();
    r_ocs.assign(RT*r);
}

void RigidBody::objectToWorldCoordinates(const Vector3D & r_ocs, Vector3D & r_wcs)const{
  const Matrix3x3 & R = getRotationMatrix();
  r_wcs.assign(getPosition() + R* r_ocs);
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

void RigidBody::calculateDynamics()
{
  calculateAcceleration();
  calculateAngularAcceleration();
}
void RigidBody::calculateCachedValues()
{
  calculateRotationMatrices();
  calculateInvertedInertiaTensorInWorldCoordinates();
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
 const Vector3D & RigidBody::getTorque()const{
   return _tau;
 }
const Vector3D & RigidBody::getPosition()const {return _x;}
void RigidBody::setPosition(const Vector3D & r){_x = r;}

const Vector3D & RigidBody::getVelocity()const {return _xDot;}
void RigidBody::setVelocity(const Vector3D & rDot){_xDot = rDot;}

const Vector3D & RigidBody::getAngularAcceleration()const {
  return _omegaDot;
}

void RigidBody::calculateAngularAcceleration(){  
  if(_m==0){
    _omegaDot = Vector3D::Zero();
    return;
  }
  const Matrix3x3 & J_inverted_wcs = getInvertedInertiaTensorInWorldCoordinates();
  _omegaDot = J_inverted_wcs *(_tau - (_omega ^ (J_inverted_wcs*_omega)));
}

const Vector3D & RigidBody::getAngularVelocity()const{return _omega;}
void RigidBody::setAngularVelocity(const Vector3D & omega){_omega = omega;}

const IBDS::Quaternion & RigidBody::getOrientation()const {return _q;}
void RigidBody::setOrientation(const IBDS::Quaternion & R){_q = R;}

const Matrix3x3 & RigidBody::getRotationMatrix()const{
  return _R;
}
const Matrix3x3 & RigidBody::getTransposedRotationMatrix()const{
  return _RT;
}
void RigidBody::calculateRotationMatrices(){
  const Quaternion & q = getOrientation();
  q.getMatrix3x3(_R);
  Matrix3x3::transpose(_R,_RT);
}


Real RigidBody::getMass()const{return _m;}
void RigidBody::setMass(Real mass){ _m = mass;}

void RigidBody::setInertiaTensor(const Matrix3x3 & inertia){
  _J=inertia;
  calculateInvertedInertiaTensor();
}
const Matrix3x3 &  RigidBody::getInertiaTensor()const{return _J;}

const Matrix3x3 & RigidBody::getInvertedInertiaTensor() const {
	return _J_inv_ocs;
}

void RigidBody::calculateInvertedInertiaTensor(){
  const Matrix3x3 & J = getInertiaTensor();
  _J_inv_ocs=Matrix3x3::Zero();
  _J_inv_ocs(0,0) = 1.0/J(0,0);
	_J_inv_ocs(1,1) = 1.0/J(1,1);
	_J_inv_ocs(2,2) = 1.0/J(2,2);
}

const Matrix3x3 & RigidBody::getInvertedInertiaTensorInWorldCoordinates()const{   
  return *&_J_inv_wcs;
}
Matrix3x3 tmp;
void RigidBody::calculateInvertedInertiaTensorInWorldCoordinates(){
  const Matrix3x3 & J_inv_ocs = getInvertedInertiaTensor();
  const Matrix3x3 & R = getRotationMatrix();
  const Matrix3x3 & RT = getTransposedRotationMatrix();
  Matrix3x3::multiply(tmp,RT,_J_inv_wcs);
  Matrix3x3::multiply(R,tmp,_J_inv_wcs);
}

void RigidBody::applyImpulse(const Vector3D& a_wcs, const Vector3D & p_wcs){
  Real m = getMass();
  if(m==0)return;
  Vector3D vDelta = (1/m) * p_wcs;
  const Matrix3x3 & J_inv_wcs = getInvertedInertiaTensorInWorldCoordinates();  
  const Vector3D & s_wcs = getPosition();
  Vector3D r_a_wcs = a_wcs-s_wcs;
  Vector3D omegaDelta= J_inv_wcs * ( r_a_wcs ^ p_wcs);

  _xDot += vDelta;
  _omega += omegaDelta;
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

 void RigidBody::calculateK(Matrix3x3 & K, const Vector3D & a_wcs, const Vector3D & b_wcs)const{
  Real m = getMass();
  if (m == 0) { 
    K.assign(Matrix3x3::Zero());
    return;
  }
  const Vector3D & s_wcs = getPosition();
  const Matrix3x3 & E_3 = Matrix3x3::Identity();
  
  Vector3D r_a_wcs = a_wcs - s_wcs;
  Vector3D r_b_wcs = b_wcs - s_wcs;

	//Matrix3x3 r_a_star,r_b_star;
  //SimMath::crossProductMatrix(r_a_wcs,r_a_star);
  //SimMath::crossProductMatrix(r_b_wcs,r_b_star);
  
  const Matrix3x3 & J_inv_wcs = getInvertedInertiaTensorInWorldCoordinates();
  Matrix3x3 tmpA(0);
  Matrix3x3 tmpB(0);
  
  //optimized code. uses inline functions
  SimMath::crossProductMatrix(r_b_wcs,tmpA);
  //tmpA = r_b_star
  Matrix3x3::multiply(J_inv_wcs,tmpA,tmpB);
  //tmpB = J_inv_wcs * r_b_star
  SimMath::crossProductMatrix(r_a_wcs,tmpA);
  //tmpA = r_a_star
  Matrix3x3::multiply(tmpA,tmpB,K);
  // K = r_a_star * J_inv_wcs * r_b_star
  tmpA.setZero();
  Real m_inv=1/m;
  tmpA(0,0)=m_inv;
  tmpA(1,1)=m_inv;
  tmpA(2,2)=m_inv;
  //tmpA = 1/m * E_3
  Matrix3x3::subtract(tmpA,K,K);
//original:   K.assign((1/m)*E_3 - r_a_star * J_inv_wcs * r_b_star);
};
  


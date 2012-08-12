#include "RigidBody.h"
#include <math/definitions.h>

using namespace nspace;



RigidBody::RigidBody(){

}

RigidBody::~RigidBody() {

}

void RigidBody::calculateDynamics()
{
  //if mass is zero all movement is stopped
  if(_m==0){
    _kinematics.angularAcceleration().setZero();
    _kinematics.angularVelocity().setZero();
    _kinematics.acceleration().setZero();
    _kinematics.velocity().setZero();
    return;
  }

  //evaluate motion equation
  _kinematics.acceleration() = _f*(1/_m);    
  const Matrix3x3 & J_inverted_wcs = getInvertedInertiaTensorInWorldCoordinates();
  _kinematics.angularAcceleration() = ( J_inverted_wcs *(_tau - (_kinematics.angularVelocity() ^ (J_inverted_wcs*_kinematics.angularVelocity()))) );

}
void RigidBody::calculateCachedValues()
{
  _kinematics.calculateRotationMatrices();
  calculateInvertedInertiaTensorInWorldCoordinates();
}


void RigidBody::addExternalForce(const Vector3D & position, const Vector3D & f){
  //_forceAccumulator
  Vector3D r = position - _kinematics.position();
  // calculate torque
  Vector3D torque = r ^ f; 
  // add force and torque to their accumulators
  _f+= f;
  _tau += torque;
}

void RigidBody::addExternalForce(const Vector3D & f){
  _f+= f;
}

void RigidBody::resetForce() {
	_f = Vector3D();
	_tau = Vector3D();
}


void RigidBody::addExternalTorque(const Vector3D & torque){
  _tau += torque;
}

 const Vector3D & RigidBody::getForce()const{
   return _f;
 }
 const Vector3D & RigidBody::getTorque()const{
   return _tau;
 }



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
  //_kinematics.calculateRotationMatrices();
  const Matrix3x3 & R = *_kinematics.getCachedRotationMatrix();//getRotationMatrix();
  const Matrix3x3 & RT = *_kinematics.getCachedTransposedRotationMatrix();//
  //MatrixOps::multiplyMatrix(tmp,J_inv_ocs,R);
  //MatrixOps::multiplyMatrix(_J_inv_wcs,RT,tmp);

  _J_inv_wcs = RT*J_inv_ocs*R;
  //Matrix3x3::multiply(tmp,RT,_J_inv_wcs);
  //Matrix3x3::multiply(R,tmp,_J_inv_wcs);
}

void RigidBody::applyImpulse(const Vector3D& a_wcs, const Vector3D & p_wcs){
  Real m = getMass();
  if(m==0)return;
  Vector3D vDelta = (1/m) * p_wcs;
  const Matrix3x3 & J_inv_wcs = getInvertedInertiaTensorInWorldCoordinates();  
  const Vector3D & s_wcs = _kinematics.position();
  Vector3D r_a_wcs = a_wcs-s_wcs;
  Vector3D omegaDelta= J_inv_wcs * ( r_a_wcs ^ p_wcs);

  _kinematics.velocity() = _kinematics.velocity()+vDelta;
  _kinematics.angularVelocity() = _kinematics.angularVelocity() +omegaDelta;
  
}

/*
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
}*/

 void RigidBody::calculateK(Matrix3x3 & K, const Vector3D & a_wcs, const Vector3D & b_wcs)const{
  Real m = getMass();
  if (m == 0) { 
    K = Matrix3x3::Zero();
    return;
  }
  const Vector3D & s_wcs = _kinematics.position();
  const Matrix3x3 & E_3 = Matrix3x3::Identity();
  
  Vector3D r_a_wcs = a_wcs - s_wcs;
  Vector3D r_b_wcs = b_wcs - s_wcs;

	//Matrix3x3 r_a_star,r_b_star;
  //SimMath::crossProductMatrix(r_a_wcs,r_a_star);
  //SimMath::crossProductMatrix(r_b_wcs,r_b_star);
  
  const Matrix3x3 & J_inv_wcs = getInvertedInertiaTensorInWorldCoordinates();
  Matrix3x3 tmpA;
  Matrix3x3 tmpB;
  
  //optimized code. uses inline functions
  
  crossProductMatrix(tmpA,r_b_wcs);
  //tmpA = r_b_star
  tmpB = J_inv_wcs *tmpA;
  //tmpB = J_inv_wcs * r_b_star
  crossProductMatrix(tmpA,r_a_wcs);
  //tmpA = r_a_star
  K = tmpA*tmpB;
  // K = r_a_star * J_inv_wcs * r_b_star
  tmpA.setZero();
  Real m_inv=1/m;
  tmpA(0,0)=m_inv;
  tmpA(1,1)=m_inv;
  tmpA(2,2)=m_inv;
  //tmpA = 1/m * E_3
  K = tmpA-K;
//original:   K.assign((1/m)*E_3 - r_a_star * J_inv_wcs * r_b_star);
};
  


#include "RigidBody.h"
#include <Math/Quaternion.h>
#include <Math/SimMath.h>

using namespace IBDS;

const TypeId RigidBody::type = "RigidBody";

const TypeId RigidBody::getBodyType()const{
  return type;
}

RigidBody::RigidBody(){

}

RigidBody::~RigidBody() {

}




void RigidBody::getDerivedState(Real * xDot)const{_kinematics.getDerivedState(xDot);}
void RigidBody::setState(const Real * state){_kinematics.setState(state);}
void RigidBody::getState(Real * state)const{_kinematics.getState(state);}
int RigidBody::getStateDimension()const{return _kinematics.getStateDimension();}


void RigidBody::calculateDynamics()
{
  if(_m==0){
    _kinematics.angularAcceleration().setZero();
    _kinematics.angularVelocity().setZero();
    _kinematics.acceleration().setZero();
    _kinematics.velocity().setZero();
    return;
  }
  _kinematics.acceleration() = _f*(1/_m);    
  const Matrix3x3 & J_inverted_wcs = getInvertedInertiaTensorInWorldCoordinates();
  _kinematics.angularAcceleration() = ( J_inverted_wcs *(_tau - (_kinematics.angularVelocity() ^ (J_inverted_wcs*_kinematics.angularVelocity()))) );

}
void RigidBody::calculateCachedValues()
{
  _kinematics.calculateRotationMatrices();
  calculateInvertedInertiaTensorInWorldCoordinates();
}


void RigidBody::addExternalForce(const IBDS::Vector3D & position, const IBDS::Vector3D & f){
  //_forceAccumulator
  Vector3D r = position - _kinematics.position();
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
  const Matrix3x3 & R = _kinematics.getRotationMatrix();
  const Matrix3x3 & RT = _kinematics.getTransposedRotationMatrix();
  Matrix3x3::multiply(tmp,RT,_J_inv_wcs);
  Matrix3x3::multiply(R,tmp,_J_inv_wcs);
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
    K.assign(Matrix3x3::Zero());
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
  


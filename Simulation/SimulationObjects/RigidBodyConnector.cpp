#include "RigidBodyConnector.h"
using namespace IBDS;

RigidBodyConnector::RigidBodyConnector(RigidBody* b, Vector3D *r)
{
	_rigidBody = b;
	
	_r = *r;

}

RigidBodyConnector::~RigidBodyConnector(void)
	{
	}

const Vector3D &  RigidBodyConnector::getPosition() const {
	/*return new Vector3D(_rigidBody->getPosition() + *get_r_new());*/
	return _r;
}

const Vector3D &  RigidBodyConnector::getVelocity()const {
  Vector3D v = _rigidBody->getVelocity() + _rDot;
	return *(new Vector3D( v));
}	

void RigidBodyConnector::addExternalForce(const Vector3D &f) {
  _rigidBody->addExternalForce(getWorldPosition(),f);//*get_r_new(),f);
	}

const Vector3D & RigidBodyConnector::getNextPosition(Real h) const {
	Vector3D nextMassCenterPosition = _rigidBody->getPosition() + h * _rigidBody->getVelocity() + (h * h / 2) * _rigidBody->getAcceleration();
	return *(new Vector3D(nextMassCenterPosition + _r));	// by now, _r has been updated via integration 
}

void RigidBodyConnector::applyImpulse(const Vector3D & p){
	if (_rigidBody->getMass() == 0) return;

	Vector3D *newVelocity = new Vector3D(_rigidBody->getVelocity() + ((1 / _rigidBody->getMass()) * p));
	_rigidBody->setVelocity(*newVelocity);

	const Matrix3x3 & invertedIntertiaTensor = _rigidBody->getInvertedInertiaTensor();

	Matrix3x3 R, RT;
	Quaternion q = _rigidBody->getOrientation();
	q.getMatrix3x3(R);
	q.getMatrix3x3T(RT);
	Matrix3x3 J_inverted_wcs = R*invertedIntertiaTensor*RT;

	//_rigidBody->setAngularVelocity(_rigidBody->getAngularVelocity() + invertedIntertiaTensor * (*get_r_new() ^ *p));
	_rigidBody->setAngularVelocity(*(new Vector3D(_rigidBody->getAngularVelocity() + invertedIntertiaTensor * (/*_r*/_rOld ^ p))));
}

const Matrix3x3 & RigidBodyConnector::getKMatrix() const {
  return _rigidBody->calculateK(_rOld,_rOld);
 /* Real m = _rigidBody->getMass();
  if (m == 0) return Matrix3x3::Zero();

  const Matrix3x3 & E_3 = Matrix3x3::Identity();

	Matrix3x3 r_star = SimMath::crossProductMatrix(_rOld);
  
	Matrix3x3 R, RT;

	Quaternion q = _rigidBody->getOrientation();
	q.getMatrix3x3(R);
	q.getMatrix3x3T(RT);
	
 const Matrix3x3 & J_inv = _rigidBody->getInvertedInertiaTensor();
	Matrix3x3 J_inv_wcs = R*J_inv*RT;
  
  Matrix3x3 K = (1/m)*E_3 - r_star * J_inv_wcs * r_star;

	return *(new Matrix3x3(K));*/
}

void RigidBodyConnector::evaluate() {
	_rigidBody->evaluate();
	/*_rDot = _rigidBody->getVelocity() + (_rigidBody->getAngularVelocity() ^ _r);*/
	_rDot = _rigidBody->getAngularVelocity() ^ _r;
}

void RigidBodyConnector::setState(const Real * state){
	_rOld = _r;

	_r[0] = state[0];
	_r[1] = state[1];
	_r[2] = state[2];
	}

void RigidBodyConnector::getState(Real * state)const{
	state[0] = _r[0];
	state[1] = _r[1];
	state[2] = _r[2];
	}

void RigidBodyConnector::getDerivedState(Real * xDot)const{
	xDot[0] = _rDot[0];
	xDot[1] = _rDot[1];
	xDot[2] = _rDot[2];
	}

int RigidBodyConnector::getStateDimension()const{
	return 3;
	}


const Vector3D &  RigidBodyConnector::calculateWorldPosition()const{
   return _rigidBody->toWorldCoordinates(_r);

}
const Vector3D & RigidBodyConnector::calculateWorldVelocity()const{
  const Vector3D & v_s = _rigidBody->getVelocity();
   Vector3D v = v_s + getVelocity();
  
  return *(new Vector3D(v));
}
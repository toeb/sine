#include "RigidBodyConnector.h"
using namespace IBDS;

Vector3D _rOld;

RigidBodyConnector::RigidBodyConnector(void)
	{
	}

RigidBodyConnector::RigidBodyConnector(RigidBody* b, Vector3D *r)
	{
	_rigidBody = b;
	
	/*Quaternion q;
	Matrix3x3 R;
	q = b->getOrientation();
	q.conjugate().getMatrix3x3(R);
	_r = new Vector3D(R * (*r));*/

	_r = *r;
	_rDot = _rigidBody->getAngularVelocity() ^ _r;
}

RigidBodyConnector::~RigidBodyConnector(void)
	{
	}

const Vector3D * RigidBodyConnector::getPosition() const {
	/*return new Vector3D(_rigidBody->getPosition() + *get_r_new());*/
	return new Vector3D(_rigidBody->getPosition() + _r);
}

const Vector3D * RigidBodyConnector::getVelocity() {
	/*return new Vector3D(_rigidBody->getVelocity() + (_rigidBody->getAngularVelocity() ^ *get_r_new()));*/
	/*_rDot = _rigidBody->getVelocity() + (_rigidBody->getAngularVelocity() ^ _r);
	return &_rDot;*/
	return new Vector3D(_rigidBody->getVelocity() + _rDot);
}	

//const Vector3D * RigidBodyConnector::get_r_new() const {
//	Quaternion q;
//	Matrix3x3 R;
//	q = _rigidBody->getOrientation();
//	q.getMatrix3x3(R);
//
//	return new Vector3D(R*(*_r));;
//}

void RigidBodyConnector::addExternalForce(const Vector3D &f) {
	_rigidBody->addExternalForce(*getPosition(),f);//*get_r_new(),f);
	}

const Vector3D * RigidBodyConnector::getNextPosition(Real h) const {
	Vector3D nextMassCenterPosition = _rigidBody->getPosition() + h * _rigidBody->getVelocity() + (h * h / 2) * _rigidBody->getAcceleration();
	return new Vector3D(nextMassCenterPosition + _r);	// by now, _r has been updated via integration 
	}

void RigidBodyConnector::applyImpulse(Vector3D const * const p){
	if (_rigidBody->getMass() == 0) return;

	Vector3D *newVelocity = new Vector3D(_rigidBody->getVelocity() + ((1 / _rigidBody->getMass()) * *p));
	_rigidBody->setVelocity(*newVelocity);

	Matrix3x3 invertedIntertiaTensor = *(_rigidBody->getInvertedInertiaTensor());

	Matrix3x3 R, RT;
	Quaternion q = _rigidBody->getOrientation();
	q.getMatrix3x3(R);
	q.getMatrix3x3T(RT);
	Matrix3x3 J_inverted_wcs = R*invertedIntertiaTensor*RT;

	//_rigidBody->setAngularVelocity(_rigidBody->getAngularVelocity() + invertedIntertiaTensor * (*get_r_new() ^ *p));
	_rigidBody->setAngularVelocity(*(new Vector3D(_rigidBody->getAngularVelocity() + invertedIntertiaTensor * (/*_r*/_rOld ^ *p))));
}

Matrix3x3 const * const RigidBodyConnector::getKMatrix() const {
	if (_rigidBody->getMass() == 0) return new Matrix3x3(Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0));

	Matrix3x3 idMatrix;
	//Matrix3x3 crossProductMatrix = SimMath::crossProductMatrix(*get_r_new());
	Matrix3x3 crossProductMatrix = SimMath::crossProductMatrix(_rOld);

	Matrix3x3 R, RT;
	Quaternion q = _rigidBody->getOrientation();
	q.getMatrix3x3(R);
	q.getMatrix3x3T(RT);
	Matrix3x3 invertedIntertiaTensor = *(_rigidBody->getInvertedInertiaTensor());
	Matrix3x3 J_inverted_wcs = R*invertedIntertiaTensor*RT;

	Matrix3x3 *K=new Matrix3x3(((1 / _rigidBody->getMass()) * idMatrix) - crossProductMatrix * invertedIntertiaTensor * crossProductMatrix);	
	return K;
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
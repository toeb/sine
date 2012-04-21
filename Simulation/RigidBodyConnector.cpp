#include "RigidBodyConnector.h"
using namespace IBDS;
RigidBodyConnector::RigidBodyConnector(void)
	{
	}
	
RigidBodyConnector::RigidBodyConnector(RigidBody* b, Vector3D *r)
	{
		_rigidBody = b;
		Quaternion q;
		Matrix3x3 R;
		q = b->getOrientation();
		q.conjugate().getMatrix3x3(R);
		_r = new Vector3D(R * (*r));
	}

RigidBodyConnector::~RigidBodyConnector(void)
	{
	}
	
const Vector3D * RigidBodyConnector::getPosition() const
{
	return new Vector3D(_rigidBody->getPosition() + *get_r_new());
}

const Vector3D * RigidBodyConnector::getVelocity() const
{
	return new Vector3D(_rigidBody->getVelocity() + (_rigidBody->getAngularVelocity() ^ *get_r_new()));
}

const Vector3D * RigidBodyConnector::get_r_new() const {
	Quaternion q;
	Matrix3x3 R;
	q = _rigidBody->getOrientation();
	q.getMatrix3x3(R);
	
	return new Vector3D(R*(*_r));;
}

void RigidBodyConnector::addExternalForce(const Vector3D &f) {
	_rigidBody->addExternalForce(*getPosition(),f);//*get_r_new(),f);
}
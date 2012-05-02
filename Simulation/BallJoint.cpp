#include "BallJoint.h"
using namespace IBDS;
BallJoint::BallJoint(void)
	{
	}
	
BallJoint::~BallJoint(void)
	{
	}

BallJoint::BallJoint(Connector *c1, Connector *c2, Real distanceTolerance, Real velocityTolerance) {
	_c1 = c1;
	_c2 = c2;
	_distanceTolerance = distanceTolerance;
	_velocityTolerance = velocityTolerance;
	evaluateKInverse();
}

bool BallJoint::correctPosition(Real h) {
	Vector3D const *a;
	Vector3D const *b;
	a = _c1->getNextPosition(h);
	b = _c2->getNextPosition(h);
	
	Vector3D distVector = *b - *a;
	if (distVector.length() < _distanceTolerance) return true;
	
	Vector3D v = (1/h) * distVector;
	Vector3D *p_a = new Vector3D(_KInverse * v);
	Vector3D *p_b = new Vector3D(-(_KInverse * v));
	_c1->applyImpulse(p_a);
	_c2->applyImpulse(p_b);
	return false;
}

void BallJoint::correctVelocity() {
	Vector3D const *v_a;
	Vector3D const *v_b;
	v_a = _c1->getVelocity();
	v_b = _c2->getVelocity();
	
	Vector3D v_rel;
	v_rel = *v_b - *v_a;
	
	evaluateKInverse();
	Vector3D *p_a = new Vector3D(_KInverse * v_rel);
	Vector3D *p_b = new Vector3D(-(_KInverse * v_rel));
	_c1->applyImpulse(p_a);
	_c2->applyImpulse(p_b);
}

void BallJoint::evaluateKInverse() {
	Matrix3x3 const *K_a = _c1->getKMatrix();
	Matrix3x3 const *K_b = _c2->getKMatrix();

	Matrix3x3 K = *K_a + *K_b;
	// if the sum of the matrices is 0, do not invert it: use 0 for the inverse matrix, too, instead
	if (K(0,0) == 0 && K(0,1) == 0 && K(0,2) == 0 && K(1,0) == 0 && K(1,1) == 0 && K(1,2) == 0 && K(2,0) == 0 && K(2,1) == 0 && K(2,2) == 0)
		_KInverse = Matrix3x3(Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0));
	else 
		_KInverse = K.symmInverse();
}

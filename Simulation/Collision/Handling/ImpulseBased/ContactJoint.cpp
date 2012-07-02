#include "ContactJoint.h"
#include <Math/Matrix3x3.h>
using namespace IBDS;

ContactJoint::ContactJoint(
  DynamicContact &contact, 
  const Real pTol, 
  const Vector3D &normal)
	: 
  _contact(contact),
  _positionTolerance(pTol),
  _normal(normal) 
{}

void ContactJoint::calculateDistancePreview(Real h, Vector3D & d)const{
	Vector3D a,b;
  connectorA().previewPosition(h,a);
  connectorB().previewPosition(h,b);
	d.assign(b-a);
}

void ContactJoint::correctPosition(Real h) {
	// get approximation of next distance
	Vector3D d;
	calculateDistancePreview(h,d);  
	// store length of distance vector
	_positionError = d.length();

	/* Actually, a normal for t+h (preview) should be used! */
	Vector3D::dotProduct(d, _normal, _positionError);

	// do not enforce contact if there is no interpenetration
	if (_positionError >= 0) return;

	// abort if positions are within tolerance
	if(arePositionsCorrect())return;

	//approximate velocity
	Vector3D v = (1/h) * _positionError * _normal;

	// calculate impulse correction
	Matrix3x3  K_aa(0);
	Matrix3x3  K_bb(0);
	connectorA().calculateCachedValues();
	connectorB().calculateCachedValues();
	const Vector3D & a_wcs = connectorA().getCachedWorldPosition();
	const Vector3D & b_wcs = connectorB().getCachedWorldPosition();

	connectorA().getKMatrix(K_aa,a_wcs,a_wcs);
	connectorB().getKMatrix(K_bb,b_wcs,b_wcs);

	Matrix3x3 K = K_aa + K_bb;

	Vector3D p_a;
	// if the sum of the matrices is 0, do not invert it: use 0 for the inverse matrix, too, instead
	if (K.isZero()) {
    p_a.setZero();
	}
	else {
		Real denominator;
		Vector3D::dotProduct(_normal, K * _normal, denominator);
		Vector3D::multiplyScalar(1 / denominator, v, p_a); 
		}
	Vector3D p_b = -p_a;

	//apply correction impulse
	contact().applyNormalImpulse(p_a);
}

bool ContactJoint::arePositionsCorrect(){
	return abs(_positionError) < _positionTolerance;
	}

void ContactJoint::correctVelocity() {	/* not used	*/ }

void ContactJoint::precompute(){}


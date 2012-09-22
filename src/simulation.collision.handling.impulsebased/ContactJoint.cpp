#include "ContactJoint.h"
#include <math/core.h>
using namespace nspace;

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
  
  d = b-a;
}

void ContactJoint::applyNormalImpulses(Matrix3x3 &K, Vector3D &v_n, Vector3D &p_a_n) {
	// do not enforce contact if there is no interpenetration
	if (_positionError_n < 0) {
		Real denominator_n;
    //denominator_n = _normal * (K*_normal);
    matrix::innerProduct(denominator_n,_normal,(K )* (_normal));
    p_a_n = (1/denominator_n)*v_n;
		contact().applyNormalImpulse(p_a_n);
		}
	}

void ContactJoint::simulateStaticFriction(Real h, Vector3D& d, Vector3D& v_n, Matrix3x3 &K_gc) {
	// approximation of tangential velocity based on a distance preview:
	Vector3D v_t = (1/h) * d - v_n;		
	Vector3D tangent(v_t);
	if (tangent.norm() != 0) {
		tangent.normalize();

		Real denominator_t;
		Vector3D p_a_t;
    matrix::innerProduct(denominator_t,tangent,K_gc*tangent);
		//denominator_t = tangent * (K_gc * tangent);
		p_a_t = (1 / denominator_t) * v_t;
		contact().applyTangentialImpulse(p_a_t);
		}
	}

void ContactJoint::simulateDynamicFriction(Vector3D &p_a_n, Vector3D &u_rel_t, Matrix3x3 &K_gc) {
	Vector3D tangent(u_rel_t);
	tangent.normalize();

	Real denominator_t;
	Vector3D p_a_t_max;
	//denominator_t = tangent * (K_gc * tangent);
   matrix::innerProduct(denominator_t,tangent,K_gc*tangent);
	p_a_t_max = (1 / denominator_t) * u_rel_t;

	Real combinedFrictionCoefficient = contact().collidableA().getDynamicFrictionCoefficient() + contact().collidableB().getDynamicFrictionCoefficient();
	Vector3D p_a_t;
	p_a_t =(combinedFrictionCoefficient * p_a_n.norm())*tangent;	// insert friction coefficient here

	Real dotProduct1, dotProduct2;
  matrix::innerProduct(dotProduct1,tangent,p_a_t_max);
  matrix::innerProduct(dotProduct2,tangent,p_a_t);
  //dotProduct1 = tangent *p_a_t_max;
	//dotProduct2 = tangent *p_a_t;



	// apply either p_a_t or p_a_t_max, whichever is weaker 
	// this ensures that the movement is slowed down but does not have its direction inverted
	if (dotProduct1 > dotProduct2) 
		contact().applyTangentialImpulse(p_a_t);
	else 
		contact().applyTangentialImpulse(p_a_t_max);
	}

void ContactJoint::applyTangentialImpulses(Real h, Vector3D& d, Vector3D& v_n, Vector3D& p_a_n) {
	const Vector3D & a_wcs = connectorA().getCachedWorldPosition();
	const Vector3D & b_wcs = connectorB().getCachedWorldPosition();

	Vector3D u_rel, u_rel_t, u_rel_n;
	contact().getRelativeVelocityVector(u_rel);
	contact().getNormalRelativeVelocityVector(u_rel_n);
	u_rel_t = u_rel - u_rel_n;

	// K matrix for impulses applied at the center of gravity of the first body to achieve a desired velocity change in the point a
  Matrix3x3 K_agc_a;
	// K matrix for impulses applied at the center of gravity of the second body to achieve a desired velocity change in the point b
	Matrix3x3 K_bgc_b;	
	connectorA().getKMatrix(K_agc_a,contact().connectorA().body().getCenterOfGravity(),a_wcs);
	connectorB().getKMatrix(K_bgc_b,contact().connectorB().body().getCenterOfGravity(),b_wcs);
	Matrix3x3 K_gc = K_agc_a + K_bgc_b;

	if (u_rel_t.norm() < EPSILON) {
		simulateStaticFriction(h, d, v_n, K_gc);
	} else {
		simulateDynamicFriction(p_a_n, u_rel_t, K_gc);
	}
	}

void ContactJoint::correctPosition(Real h) {
	// get approximation of next distance
	Vector3D d;
	calculateDistancePreview(h,d);  
	// store length of distance vector
	_positionError_n = d.norm();

	/* Actually, a normal for t+h (preview) should be used! */
  matrix::innerProduct(_positionError_n,d,_normal);
  //_positionError_n = d * _normal;

	//approximate velocity
	Vector3D v_n = (1/h) * _positionError_n * _normal;

	// calculate impulse correction
	Matrix3x3  K_aa;
	Matrix3x3  K_bb;
	connectorA().calculateCachedValues();
	connectorB().calculateCachedValues();
	const Vector3D & a_wcs = connectorA().getCachedWorldPosition();
	const Vector3D & b_wcs = connectorB().getCachedWorldPosition();

	connectorA().getKMatrix(K_aa,a_wcs,a_wcs);
	connectorB().getKMatrix(K_bb,b_wcs,b_wcs);
	Matrix3x3 K = K_aa + K_bb;

	// if the sum of the matrices is 0, impulses must be infinite and hence cannot be applied
	if (!K.isZero()) {

		Vector3D p_a_n;
		if(!arePositionsCorrect())
			applyNormalImpulses(K, v_n, p_a_n);

		applyTangentialImpulses(h, d, v_n, p_a_n);
		}
	}


bool ContactJoint::arePositionsCorrect(){
	return abs(_positionError_n) < _positionTolerance;
	}

void ContactJoint::correctVelocity() {	/* not used	*/ }

void ContactJoint::precompute(){}


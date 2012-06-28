#include <Simulation\Collision\Handling\ContactJoint.h>
using namespace IBDS;

	ContactJoint::ContactJoint(Connector &c1, Connector &c2, const Real pTol, const Vector3D &normal): _cA(c1),_cB(c2),_positionTolerance(pTol),_normal(normal){};

	void ContactJoint::calculateDistancePreview(Real h, Vector3D & d)const{
		Vector3D a,b;
		_cA.previewPosition(h,a);
		_cB.previewPosition(h,b);
		d.assign( b-a);
		}

	void ContactJoint::correctPosition(Real h) {
		return;		/* deactivated for now because sticking between contacts needs to be resolved yet */

		// get approximation of next distance
		Vector3D d;
		calculateDistancePreview(h,d);  
		// store length of distance vector
		_positionError = d.length();

		/* Actually, a normal for t+h (preview) should be used! */
		Vector3D::dotProduct(d, _normal, _positionError);

		//abort if positions are within tolerance
		if(arePositionsCorrect())return;
		//approximate velocity
		
		Vector3D v = (1/h) * _positionError * _normal;

		// calculate impulse correction
		//evaluateKInverse();
		Matrix3x3  K_aa(0);
		Matrix3x3  K_bb(0);
		_cA.calculateCachedValues();
		_cB.calculateCachedValues();
		const Vector3D & a_wcs = _cA.getCachedWorldPosition();
		const Vector3D & b_wcs = _cB.getCachedWorldPosition();

		_cA.getKMatrix(K_aa,a_wcs,a_wcs);
		_cB.getKMatrix(K_bb,b_wcs,b_wcs);

		Matrix3x3 K = K_aa + K_bb;

		Vector3D p_a;
		// if the sum of the matrices is 0, do not invert it: use 0 for the inverse matrix, too, instead
		if (K.isZero()) {
			p_a = 0;
			}
		else {
			Real denominator;
			Vector3D::dotProduct(_normal, K * _normal, denominator);
			Vector3D::multiplyScalar(1 / denominator, v, p_a); 
			}
		Vector3D p_b = -p_a;

		//apply correction impulse
		_cA.applyImpulse(p_a);
		_cB.applyImpulse(p_b);
		}

	bool ContactJoint::arePositionsCorrect(){
		return _positionError < _positionTolerance;
		}

	void ContactJoint::correctVelocity() {
		// not used
		}

	void ContactJoint::evaluateKInverse() {
		Matrix3x3  K_aa(0);
		Matrix3x3  K_bb(0);

		const Vector3D & a_wcs = _cA.getCachedWorldPosition();
		const Vector3D & b_wcs = _cB.getCachedWorldPosition();

		_cA.getKMatrix(K_aa,a_wcs,a_wcs);
		_cB.getKMatrix(K_bb,b_wcs,b_wcs);

		Matrix3x3 K = K_aa + K_bb;
		// if the sum of the matrices is 0, do not invert it: use 0 for the inverse matrix, too, instead
		if (K.isZero())
			_KInverse = Matrix3x3::Zero();
		else 
			Matrix3x3::symmInverse(K,_KInverse);//_KInverse = K.symmInverse();
		}

	void ContactJoint::precompute(){
		evaluateKInverse();
		}


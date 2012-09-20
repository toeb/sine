#pragma once
#include <simulation.dynamics.multibody.impulsebased/Joint.h>
#include <simulation.collision.handling.impulsebased/DynamicContact.h>

namespace nspace {
class ContactJoint : public Joint {
private:
	DynamicContact &_contact;
	// contact normal
	Vector3D _normal;	
	const Real _positionTolerance;	
	Real _positionError_n;
	void calculateDistancePreview(Real h, Vector3D & d) const;

	void applyNormalImpulses(Matrix3x3 &K, Vector3D &v_n, Vector3D &p_a_n);
	void simulateStaticFriction(Real h, Vector3D& d, Vector3D& v_n, Matrix3x3 &K_gc);
	void simulateDynamicFriction(Vector3D &p_a_n, Vector3D &u_rel_t, Matrix3x3 &K_gc);
	void applyTangentialImpulses(Real h, Vector3D& d, Vector3D& v_n, Vector3D& p_a_n);

public: 
	ContactJoint(DynamicContact &contact, const Real pTol, const Vector3D &normal);
  inline DynamicContact & contact(){return _contact;}
  inline const DynamicContact & contact()const{return _contact;}
  inline DynamicConnector & connectorA()const{return contact().connectorA();}
  inline DynamicConnector & connectorB()const{return contact().connectorB();}
  inline DynamicConnector & connectorA(){return contact().connectorA();}
  inline DynamicConnector & connectorB(){return contact().connectorB();}

	void correctPosition(Real h);
	bool arePositionsCorrect();
	void correctVelocity();
	void precompute();

};
}
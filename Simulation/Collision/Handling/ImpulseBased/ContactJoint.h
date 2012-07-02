#pragma once
#include <Simulation/MultiBodyDynamics/Joint.h>
#include <Simulation/Collision/Handling/ImpulseBased/DynamicContact.h>

namespace IBDS {
class ContactJoint : public Joint {
private:
	DynamicContact &_contact;
	// contact normal
	Vector3D _normal;	
	const Real _positionTolerance;	
	Real _positionError;
	void calculateDistancePreview(Real h, Vector3D & d) const;
public: 
	ContactJoint(DynamicContact &contact, const Real pTol, const Vector3D &normal);
  inline DynamicContact & contact(){return _contact;}
  inline const DynamicContact & contact()const{return _contact;}
  inline Connector & connectorA()const{return contact().connectorA();}
  inline Connector & connectorB()const{return contact().connectorB();}
  inline Connector & connectorA(){return contact().connectorA();}
  inline Connector & connectorB(){return contact().connectorB();}

	void correctPosition(Real h);
	bool arePositionsCorrect();
	void correctVelocity();
	void precompute();

};
}
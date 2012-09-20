#pragma once

#include <simulation.dynamics/Connection/Connector.h>

#include <simulation.collision/Contact.h>

#include <simulation.collision.handling.impulsebased/DynamicCollidable.h>

namespace nspace{

enum ContactType {COLLISION, RESTING_CONTACT, DRIFTING_APART, UNKNOWN};

class DynamicContact{
	private:
		Contact _contact;

		DynamicConnector *_cA;
		DynamicConnector *_cB;

		DynamicCollidable & _collidableA;
		DynamicCollidable & _collidableB;
    
		Vector3D _accumulatedImpulse;
  public:

		Contact & contact(){return _contact;}

		/**
		* Creates a Contact instance. 
		* body1 and body2 are the two contacting dynamic bodies (needed to apply collision response),
		* pA_wcs_in and pB_wcs_in are the coordinates of the respective contact points,
		* normal_in - the contact normal,
		* penetrationDepth_in - the depth of the penetration
		*/
		DynamicContact(
			DynamicCollidable &collidableA, 
			DynamicCollidable &collidableB, 
			Contact &contact);
    ~DynamicContact();

		void getRelativeVelocityVector (Vector3D & out);
		void getNormalRelativeVelocity(Real &out);
		void getNormalRelativeVelocityVector (Vector3D &out);

		ContactType classify();

		inline DynamicCollidable & collidableA(){return _collidableA;};
		inline DynamicCollidable & collidableB(){return _collidableB;};

		inline DynamicConnector& connectorA(){return *_cA;}
		inline DynamicConnector& connectorB(){return *_cB;}

		inline DynamicConnector& connectorA() const{return *_cA;}
		inline DynamicConnector& connectorB() const{return *_cB;}

		/**
		* Applies the impulse p to the first body and -p to the second body.
		* If the resulting accumulated impulse would make the bodies stick together, 
		* an impulse is applied in order to make the accumulated impulse 0.
		*/
		void applyNormalImpulse(Vector3D &p);
    void applyTangentialImpulse(Vector3D &p);

		};

	}
#pragma once

#include <Simulation/Dynamics/Connection/Connector.h>
#include <Simulation/Collision/Contact.h>
#include <Simulation/Collision/Handling/ImpulseBased/DynamicCollidable.h>
namespace IBDS{

enum ContactType {COLLISION, RESTING_CONTACT, DRIFTING_APART, UNKNOWN};

class DynamicContact{
	private:
		Contact _contact;

		Connector *_cA;
		Connector *_cB;

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

		inline Connector& connectorA(){return *_cA;}
		inline Connector& connectorB(){return *_cB;}

		inline Connector& connectorA() const{return *_cA;}
		inline Connector& connectorB() const{return *_cB;}

		/**
		* Applies the impulse p to the first body and -p to the second body.
		* If the resulting accumulated impulse would make the bodies stick together, 
		* an impulse is applied in order to make the accumulated impulse 0.
		*/
		void applyNormalImpulse(Vector3D &p);
    void applyTangentialImpulse(Vector3D &p);

		};

	}
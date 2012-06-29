#pragma once

#include <Simulation\Dynamics\Connector.h>
#include <Simulation\MultiBodyDynamics\Joint.h>
#include <Simulation\Collision\Contact.h>

#include <Math\Vector3D.h>
#include <Math\Matrix3x3.h>


namespace IBDS {
class ContactJoint : public Joint {

private:
	Connector & _cA;
	Connector & _cB;
	Contact *_contact;

	// contact normal
	const Vector3D & _normal;
	
	const Real _positionTolerance;
	
	Real _positionError;

	void calculateDistancePreview(Real h, Vector3D & d) const;

public: 

	ContactJoint(Contact *contact, const Real pTol, const Vector3D &normal);

	void correctPosition(Real h); 

	bool arePositionsCorrect();

	void correctVelocity();

	void precompute();

	};
	}
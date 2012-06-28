#pragma once

#include <Simulation\Dynamics\Connector.h>
#include <Simulation\MultiBodyDynamics\Joint.h>

#include <Math\Vector3D.h>
#include <Math\Matrix3x3.h>

namespace IBDS {
class ContactJoint : public Joint {

private:
	Connector & _cA;
	Connector & _cB;

	// contact normal
	const Vector3D & _normal;
	
	// the inverse of the matrix K, cached for reusage across methods
	Matrix3x3 _KInverse;
	
	const Real _positionTolerance;
	
	Real _positionError;



	void calculateDistancePreview(Real h, Vector3D & d) const;

	void evaluateKInverse();

public: 
	ContactJoint(Connector &c1, Connector &c2, const Real pTol, const Vector3D &normal);

	void correctPosition(Real h); 

	bool arePositionsCorrect();

	void correctVelocity();

	void precompute();

	};
	}
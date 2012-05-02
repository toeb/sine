#pragma once
#include <Math/Vector3D.h>
#include <Math/Matrix3x3.h>
#include "Simulation/Connector.h"
#include "Joint.h"
namespace IBDS {
	/**
	 * 
	 */
	class BallJoint : public Joint
	{
	private:
		BallJoint(void);


		Connector *_c1;
		Connector *_c2;

		Real _distanceTolerance;
		Real _velocityTolerance;

		// the inverse of the matrix K, stored globally for reusage across methods
		Matrix3x3 _KInverse;

	public:
		~BallJoint(void);

		BallJoint(Connector *c1, Connector *c2, Real distanceTolerance = 1e-3, Real velocityTolerance = 1e-2);
	
		bool correctPosition(Real h);
		void correctVelocity();
		
		void evaluateKInverse();
	};
	}
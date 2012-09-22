#pragma once
#include <math/core.h>
#include <simulation.dynamics/connection/Connector.h>
#include <simulation.dynamics.multibody.impulsebased/Joint.h>
namespace nspace {
	/**
	 * 
	 */
class BallJoint : public Joint
{
private:
	DynamicConnector & _cA;
	DynamicConnector & _cB;
  // the inverse of the matrix K, cached for reusage across methods
	Matrix3x3 _KInverse;
  //tolerances
  Real _positionTolerance;
  Real _velocityTolerance;
  Real _positionError;
public:
	void precompute();
  ~BallJoint();

	BallJoint(DynamicConnector & a, DynamicConnector &b,Real positionTolerance=3e-10, Real velocityTolerance=3e-10);
	  
	inline bool arePositionsCorrect();
    
  inline void correctPosition(Real h);
	void correctVelocity();
		
  void calculateDistancePreview(Real h, Vector3D & d)const;
private:
	void  evaluateKInverse();
};
	}
#pragma once
#include <Math/Vector3D.h>
#include <Math/Matrix3x3.h>
#include <Simulation/Dynamics/Connection/Connector.h>
#include <Simulation/MultiBodyDynamics/ImpulseBased/Joint.h>
namespace IBDS {
	/**
	 * 
	 */
class BallJoint : public Joint
{
private:
	Connector & _cA;
	Connector & _cB;
  // the inverse of the matrix K, cached for reusage across methods
	Matrix3x3 _KInverse;
  //tolerances
  Real _positionTolerance;
  Real _velocityTolerance;
  Real _positionError;
public:
	void precompute();
  ~BallJoint();

	BallJoint(Connector & a, Connector &b,Real positionTolerance=3e-10, Real velocityTolerance=3e-10);
	  

	inline bool arePositionsCorrect();
    
  inline void correctPosition(Real h);
	void correctVelocity();
		
  void calculateDistancePreview(Real h, Vector3D & d)const;
private:
	void  evaluateKInverse();
};
	}
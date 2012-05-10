#pragma once
#include <Math/Vector3D.h>
#include <Math/Matrix3x3.h>
#include "Connector.h"
#include "Joint.h"
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
	void beforeCorrection();
  ~BallJoint();

	BallJoint(Connector & a, Connector &b,Real positionTolerance=3e-10, Real velocityTolerance=3e-10);
	  

	bool arePositionsCorrect();
    
  void correctPosition(Real h);
	void correctVelocity();
		
  Vector3D calculateDistancePreview(Real h)const;
private:
	void  evaluateKInverse();
};
	}
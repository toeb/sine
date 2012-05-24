#pragma once
#include <Simulation/Core/ISimulationObject.h>
#include <Math/MathDefs.h>
namespace IBDS {
class Joint : public ISimulationObject
{
public:
	
	/**
		* \param h simulation step size (for position prediction)
		*/
	virtual void precompute()=0;
	virtual inline void correctPosition(Real h) = 0;
	virtual void correctVelocity() = 0;    
	virtual inline bool arePositionsCorrect()=0;
};
}
#pragma once
#include <Simulation/ISimulationObject.h>
namespace IBDS {
class Joint : public ISimulationObject
{
public:
  
	/**
		* \param h simulation step size (for position prediction)
		*/
  virtual void beforeCorrection()=0;
	virtual void correctPosition(Real h) = 0;
	virtual void correctVelocity() = 0;    
	virtual bool arePositionsCorrect()=0;
};
}
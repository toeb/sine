#pragma once
#include <Simulation/Core/ISimulationObject.h>
#include <Math/MathDefs.h>
namespace IBDS {
class Joint : public ISimulationObject
{
public:

  /**
   * \brief Precomputes this object.
   * 				
   */
	virtual void precompute()=0;
   /**
		* \param h simulation step size (for position prediction)
		*/
	virtual inline void correctPosition(Real h) = 0;

  /**
   * \brief Correct the velocity of this joint.
   * 				
   */
	virtual void correctVelocity() = 0;    

  /**
   * \brief Query if positions are correct.
   *
   * 
   * \return true if positions correct, false if not.
   */
	virtual inline bool arePositionsCorrect()=0;
};
}
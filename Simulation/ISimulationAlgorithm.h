#pragma once
#include <Simulation/ISimulationObject.h>
#include <Math/MathDefs.h>
namespace IBDS{
class ISimulationAlgorithm:public ISimulationObject{
public:
  /**
   * \brief Adds a simulation object to this algorithm
   * 				if the algorithm accepts it it shall return true
   * 
   * \author Tobi
   * \date 12.05.2012
   *
   * \param [in,out] object If non-null, the object.
   *
   * \return true if it succeeds, false if it fails.
   */
  virtual bool addSimulationObject(ISimulationObject * object){return false;};

  /**
   * \brief Query if this algorithm is compatible with 'algorithm' the new algorithm.
   * if a subclass returns false, the new algorithm will not be added to the simulation
   * \author Tobi
   * \date 12.05.2012
   *
   * \param [in,out] algorithm If non-null, the algorithm.
   *
   * \return true if compatible with, false if not.
   */
  virtual bool isCompatibleWith(ISimulationAlgorithm * algorithm){
    return true;
  }
  /**
   * \brief Resets this object.
   *
   * \author Tobi
   * \date 12.05.2012
   */
  virtual void reset(){};

  /**
   * \brief Precompute step. This step is to be used to precompute certain values that are needed during the
   * 				following steps.    
   *
   * \author Tobi
   * \date 12.05.2012
   */
  virtual void precomputeStep(){};

  /**
   * \brief Is executed before integration.
   *
   * \author Tobi
   * \date 12.05.2012
   *
   * \param time The time.
   * \param h    The h.
   */
  virtual void preIntegrationStep(Real time, Real h){};

  /**
   * \brief Is executed in integration phase.
   *
   * \author Tobi
   * \date 12.05.2012
   *
   * \param time The time.
   * \param h    The h.
   */
  virtual void integrationStep(Real time, Real h){};

  /**
   * \brief executes after integration.
   *
   * \author Tobi
   * \date 12.05.2012
   *
   * \param time The time.
   * \param h    The h.
   */
  virtual void postIntegrationStep(Real time, Real h){};

};

}
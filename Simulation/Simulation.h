#pragma once

#include "SimulationObjects/Force.h"
#include "Integrators/Integrator.h"
#include "ISimulationObject.h"
#include "Integrators/CompositeIntegratable.h"
#include "Integrators/IIntegrable.h"
#include "SimulationObjects/Body.h"
#include "SimulationObjects/Connector.h"
#include "SimulationObjects/Joint.h"
#include <Simulation/ISimulationAlgorithm.h>

#include <vector>

namespace IBDS{

class Simulation : public ISimulationObject{
private:  
  ///< The simulation objects
  std::vector<ISimulationObject*> _simulationObjects;
  ///< The simulation algorithms
  std::vector<ISimulationAlgorithm*> _simulationAlgorithms;  
  ///< The time
  Real _time;
  ///< The target time 
  Real _targetTime;
public:

  /**
   * \brief Simulates until target time is reached.
   *
   * \author Tobi
   * \date 12.05.2012
   *
   * \param targetTime Time of the target.
   */
  void simulate(Real targetTime);

  /**
   * \brief(deletes model (also in all algorithm) and calls buildModel)
   *
   * \author Tobi
   * \date 12.05.2012
   */
  virtual void reset();

  /**
   * \brief Gets the target time.
   *
   * \author Tobi
   * \date 12.05.2012
   *
   * \return The target time.
   */
  const Real & getTargetTime();

  /**
   * \brief Gets the time.
   *
   * \author Tobi
   * \date 12.05.2012
   *
   * \return The time.
   */
  const Real & getTime();

  /**
   * \brief Initializes this object.
   *
   * \author Tobi
   * \date 12.05.2012
   *
   * \return true if it succeeds, false if it fails.
   */
  bool initialize();

  /**
   * \brief Default constructor.
   *
   * \author Tobi
   * \date 07.05.2012
   */
  Simulation();


  /**
   * \brief Destructor.
   *
   * \date 07.05.2012
   */
  ~Simulation();

  
  

  /**
   * \brief Adds a simulation object.  tries to add the object to every Algorithm
   * 				returns false if no algorithm was interested.
   * 				
   * 				the object is stored no matter what. 
   *
   * \author Tobi
   * \date 12.05.2012
   *
   * \param [in,out] simulationObject If non-null, the simulation object.
   *
   * \return true if it succeeds, false if it fails.
   */
  bool addSimulationObject(ISimulationObject * simulationObject);

  /**
   * \brief Adds a simulation algorithm. checks to see if it is compatible with the current set of algorithms
   * 				if not it returns false.
   * 				if it is compatible every currently existing simulationobject is added to the algorithm
   *
   * \author Tobi
   * \date 12.05.2012
   *
   * \param [in,out] algorithm If non-null, the algorithm.
   *
   * \return true if it succeeds, false if it fails.
   */
  bool addSimulationAlgorithm(ISimulationAlgorithm * algorithm);
protected:

  /**
   * \brief may be overridden.  gets called when a simulation object was added
   *
   * \author Tobi
   * \date 12.05.2012
   *
   * \param [in,out] object If non-null, the object.
   */
  virtual void onSimulationObjectAdded(ISimulationObject * object){};

  /**
   * \brief Builds the model.
   *
   * \author Tobi
   * \date 12.05.2012
   */
  virtual void buildModel(){};

  /**
   * \brief Builds the algorithms.
   *
   * \author Tobi
   * \date 12.05.2012
   */
  virtual void buildAlgorithms(){};
  
  
};
};
#pragma once

#include <Simulation/Integration/Integrator.h>
#include <Simulation/Core/ISimulationModule.h>

#include <set>

namespace IBDS{

class Simulation : public ISimulationObject{
private:  
  Integrator * _integrator;
  ///< The simulation objects
  std::set<ISimulationObject*> _simulationObjects;
  ///< The simulation modules
  std::set<ISimulationModule*> _simulationModules;  
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
  virtual void reset();
  const Real & getTargetTime();
  const Real & getTime();


  void setIntegrator(Integrator & integrator);
  Integrator * getIntegrator();

  Simulation();
  ~Simulation();
  
  bool addSimulationObject(ISimulationObject * simulationObject);
  bool removeSimulationObject(ISimulationObject * simulationObject);

protected:
  bool initializeObject();
  bool addSimulationModule(ISimulationModule * module);
  bool removeSimulationModule(ISimulationModule * module);
  /**
   * \brief may be overridden.  gets called when a simulation object was added
   *
   * \author Tobi
   * \date 12.05.2012
   *
   * \param [in,out] object If non-null, the object.
   */
  virtual void onSimulationObjectAdded(ISimulationObject * object){};
  virtual void onSimulationObjectRemoved(ISimulationObject * object){};
};
};
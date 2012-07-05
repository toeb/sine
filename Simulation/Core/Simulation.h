#pragma once

#include <Simulation/Integration/Integrator.h>
#include <Simulation/Core/ISimulationModule.h>
#include <Simulation/Core/Time.h>
#include <functional>
#include <set>

namespace IBDS{

class Simulation : public ISimulationObject{
private:  
  Integrator * _integrator;
  ///< The simulation objects
  std::set<ISimulationObject*> _simulationObjects;
  ///< The simulation modules
  std::set<ISimulationModule*> _simulationModules;  
  ///< The current time
  Time _time;
  ///< The target time 
  Time _targetTime;
public:

  /**
   * \brief Simulates until target time is reached.
   *
   * \param targetTime Time of the target.
   */
  void simulate(Time targetTime);
  const Time & getTargetTime();
  const Time & getTime();


  void setIntegrator(Integrator & integrator);
  Integrator * getIntegrator();

  Simulation();
  ~Simulation();
  
  bool addSimulationObject(ISimulationObject * simulationObject);
  bool removeSimulationObject(ISimulationObject * simulationObject);
  
  void foreachModule(std::function<void(ISimulationModule*)> f);
  void foreachObject(std::function<void(ISimulationObject*)> f);

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
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
  ///< The system time at time of initialization
  Time _initialSystemTime;
public:

  /**
   * \brief Adds simulationObject / simulation module to the simulation.
   * 				
   * \return true if it succeeds, false if it fails.
   */
  bool add(ISimulationObject * simulationObject);

  /**
   * \brief Removes the given simulationObject from the simulation.
   * 				
   * 				the effects might be unintended consequences depending on the modules added
   *
   * \return true if it succeeds, false if it fails.
   */
  bool remove(ISimulationObject * simulationObject);

  /**
   * \brief adds a object to the simulation
   */
  Simulation & operator <<(ISimulationObject * object){
    add(object);
  }

  /**
   * \brief remove the simulationobject from the simulation
   */
  Simulation & operator >>(ISimulationObject * object){
    remove(object);
  }

  /**
   * \brief indexer operator returns the simulation object with the name.
   *
   * \param name The name.
   *
   * \return The indexed value.
   */
  ISimulationObject * operator[](const std::string & name){
    return find(name);
  }

  /**
   * \brief Simulates until target time is reached.
   *
   * \param targetTime Time of the target.
   */
  void simulate(Time targetTime);

  const Time & getTargetTime();
  const Time & time();
  Time elapsedSystemTime()const;

  void setIntegrator(Integrator & integrator);
  Integrator * getIntegrator();

  Simulation();
  ~Simulation();
  
  
  void foreachModule(std::function<void(ISimulationModule*)> f);
  void foreachObject(std::function<void(ISimulationObject*)> f);

  ISimulationObject * find(const std::string & name);
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
}
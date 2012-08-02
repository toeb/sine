#pragma once
#include <simulation/core/ISimulationModule.h>
#include <simulation/integration/composites/CompositeSystemFunction.h>
#include <simulation/integration/composites/CompositeStatefulObject.h>
#include <simulation/integration/StepIntegrator.h>
#include <simulation/time/SimulationTimeProvider.h>
#include <simulation/core/SimulationTask.h>

namespace nspace{	

/**
 * \brief Integrable system module. 
 * 				This module accepts all integrables and system functions.
 * 				These input are combined and integrated via the integrator
 * 				When an integrator is added to the simulation and it is not used
 * 				it will replace the current integrator of this module
 * 				you can also control the integrator via the set integrator method
 *
 * \author Tobi
 * \date 13.07.2012
 */
class SystemModule : public virtual SimulationTask,
  public virtual ISimulationModule{
private:
  CompositeStatefulObject _integrable;
  CompositeSystemFunction _systemFunction;
  StepIntegrator * _integrator;
  SimulationTimeProvider & _timeProvider;
public:  
  SystemModule(SimulationTimeProvider & timeProvider);
  void setIntegrator(StepIntegrator * integrator);
  IStatefulObject & statefulObject(){return _integrable;}
  ISystemFunction & systemFunction(){return _systemFunction;}
  ITimeProvider & timeProvider(){return _timeProvider;}
protected:
  void announce(ISimulationObject * object);
  void renounce(ISimulationObject * object){}
  void run();
  bool initializeObject();
  virtual Time currentTime() const;

};
}
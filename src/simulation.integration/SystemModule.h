#pragma once

#include <core.task/ScheduledTask.h>
#include <simulation.integration/ISystemFunction.h>
#include <simulation.integration/Evaluator.h>
#include <simulation.integration/StepIntegrator.h>
#include <core/Reflection.h>
#include <core.hub/CompositeHubObject.h>

#include <simulation.time/SimulationTimeProvider.h>

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
  class IntegratingSystem :
    public virtual NamedObject,
    public virtual PropertyChangingObject,
    public virtual CompositeHubObject
  {
    REFLECTABLE_OBJECT(IntegratingSystem);
    PROPERTY(ITask*, Task);
    PROPERTY(StatefulObject*, State);
    PROPERTY(ISystemFunction*, SystemFunction);
    PROPERTY(Evaluator*, Evaluator);
    PROPERTY(SimulationTimeProvider *, TimeProvider);
    PROPERTY(StepIntegrator*, Integrator);
  public:
    void operator()();
    IntegratingSystem(SimulationTimeProvider * timeProvider);

  private:
    void timeout(Time dt, Time t);
    void setupEvaluator(StatefulObject * state, ISystemFunction * func);
  };
}

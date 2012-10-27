#pragma once

#include <core.task/ScheduledTask.h>
#include <simulation.integration/ISystemFunction.h>
#include <simulation.integration/Evaluator.h>
#include <simulation.integration/StepIntegrator.h>
#include <core/Reflection.h>
#include <core.hub/CompositeHubObject.h>

#include <simulation.time/SimulationTimeProvider.h>
#include <simulation.logging/Log.h>
namespace nspace{	

  /**
  *
  */
  class IntegratingSystem :
    public virtual NamedObject,
    public virtual PropertyChangingObject,
    public virtual CompositeHubObject,
    public virtual Log
  {
    REFLECTABLE_OBJECT(IntegratingSystem);
    PROPERTY(ITask*, Task);
    PROPERTY(StatefulObject*, State);
    PROPERTY(ISystemFunction*, SystemFunction);
    PROPERTY(Evaluator*, Evaluator);
    PROPERTY(SimulationTimeProvider *, TimeProvider);
    PROPERTY(StepIntegrator*, Integrator);
    PROPERTY(long, EvaluationCount){};
  public:
    // this object is a functor which will be used as a callback in the Task
    void operator()();
    IntegratingSystem(SimulationTimeProvider * timeProvider);
  protected:
    void onPropertyChanged(const std::string & propertyName);
  private:
    void timeout(Time dt, Time t);
    void setupEvaluator(StatefulObject * state, ISystemFunction * func);
  };
}

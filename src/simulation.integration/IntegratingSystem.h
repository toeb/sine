#pragma once

#include <core.task/ScheduledTask.h>
#include <simulation.integration/ISystemFunction.h>
#include <simulation.integration/Evaluator.h>
#include <simulation.integration/StepIntegrator.h>
#include <core.h>
#include <core.hub/CompositeHubObject.h>

#include <simulation.time/SimulationTimeProvider.h>
#include <core.logging/Log.h>
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
    reflect_type(IntegratingSystem);
    typedef ITask*                    reflect_property(Task);
    typedef StatefulObject*           reflect_property(SystemState);
    typedef ISystemFunction*          reflect_property(SystemFunction);
    typedef Evaluator*                reflect_property(Evaluator);
    typedef SimulationTimeProvider *  reflect_property(TimeProvider);
    typedef StepIntegrator*           reflect_property(Integrator);
    typedef long                      reflect_property(EvaluationCount);
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

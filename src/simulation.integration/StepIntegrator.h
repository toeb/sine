#pragma once

#include <ostream>
#include <simulation.integration/Integrator.h>
namespace nspace{
  class StepIntegrator : public virtual Integrator{
    reflect_type(StepIntegrator)
      reflect_superclasses(Integrator);

    //DESCRIPTION(LowerBound, "The lower bound of integration")
    typedef Time reflect_property(LowerBound);

    //DESCRIPTION(UpperBound, "The upper bound which is to be reached")
    typedef Time reflect_property(UpperBound);

    //DESCRIPTION(Time, "The current time 't' ")
    typedef Time reflect_property(Time);

    //DESCRIPTION(CurrentStepSize, "The current step size h(t) 'h' ")
    typedef Time reflect_property(CurrentStepSize);

    //DESCRIPTION(InitialStepSize, "The initial step size h(t)|t=0 'h0'")
    typedef Time reflect_property(InitialStepSize);
  private:
    StateMatrix x_next;
  protected:
    /**
    * <summary> Executes an integration step.</summary>
    */
    virtual void  doStep(StateMatrix & x_next, const StateMatrix & x_i, Real t_i, Real h)=0;
  public:
    bool needsIntegration()const;
    Time step();
    Time integrate();

    StepIntegrator(Real h0=0.01);
  protected:
    void integrate(Real a, Real b);
  };
}

#pragma once

#include <ostream>
#include <simulation.integration/Integrator.h>
namespace nspace{

class StepIntegrator : public virtual Integrator{
    REFLECTABLE_OBJECT(StepIntegrator)
    SUBCLASSOF(Integrator);
    
    DESCRIPTION(LowerBound, "The lower bound of integration")
    PROPERTY(Time, LowerBound);
    
    DESCRIPTION(UpperBound, "The upper bound which is to be reached")
    PROPERTY(Time, UpperBound);
    
    DESCRIPTION(Time, "The current time 't' ")
    PROPERTY(Time, Time){}
    
    DESCRIPTION(CurrentStepSize, "The current step size h(t) 'h' ")
    PROPERTY(Time, CurrentStepSize){}

    DESCRIPTION(InitialStepSize, "The initial step size h(t)|t=0 'h0'")
    PROPERTY(Time, InitialStepSize){}
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

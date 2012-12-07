#pragma once
#include <simulation/ISimulationObject.h>

#include <simulation.state/State.h>
#include <simulation.state/StatefulObject.h>

#include <simulation.integration/ISystemFunction.h>

namespace nspace{
  // class combines a stateful object with a system function 
  // which allows an Integrator to integrate its state
  class Evaluator : public virtual ISimulationObject{
  private:
    SystemState _state;
    StateMatrix _x;
    StateMatrix _xDot;
    StatefulObject & _statefulObject;
    ISystemFunction * _systemFunction;
  public:
    // constructor.  needs a stateful object.  a systemfunction is not needed.  (this results in the derived states always being zero)
    Evaluator(StatefulObject & stateful, ISystemFunction * systemFunction=0);
    // sets the state x of the evaluator
    void setX(const StateMatrix & x);
    // gets the current state x
    const StateMatrix & x();
    // gets the current derived state xdot
    const StateMatrix & xDot();
    // evaluates the evaluator at time t and setpsize h stores the result in x
    const StateMatrix & f(const StateMatrix &x, Real t, Real h);
  };
}

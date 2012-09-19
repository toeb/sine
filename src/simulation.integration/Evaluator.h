#pragma once
#include <simulation/ISimulationObject.h>
#include <simulation.integration/State.h>
#include <simulation.integration/IStatefulObject.h>
#include <simulation.integration/ISystemFunction.h>

namespace nspace{

  class Evaluator : public virtual ISimulationObject{
  private:
    State _state;
    StateMatrix _x;
    StateMatrix _xDot;
    StatefulObject & _statefulObject;
    ISystemFunction * _systemFunction;
  public:
    Evaluator(StatefulObject & stateful, ISystemFunction * systemFunction=0):
        _statefulObject(stateful),
          _systemFunction(systemFunction){
            _statefulObject.assignState(_state);  
            _statefulObject.notifyStateNeeded();
        }
        void setX(const StateMatrix & x){
          _state.setX(x);
          _statefulObject.notifyStateChanged();
        }
        const StateMatrix & x(){
          _statefulObject.notifyStateNeeded();
          _state.getX(_x);
          return _x;
        }
        const StateMatrix & xDot(){
          _statefulObject.notifyStateNeeded();
          _state.getXDot(_xDot);
          return _xDot;
        }
        const StateMatrix & f(const StateMatrix &x, Real t, Real h){
          setX(x);
          if(_systemFunction)_systemFunction->evaluate(t,h);
          return xDot();
        }
  };
}
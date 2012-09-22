#pragma once

#include <simulation/ISimulationObject.h>
#include <simulation.state/State.h>
#include <core/patterns/Composite.h>

namespace nspace{

  class StatefulObject : public virtual ISimulationObject{
  private:
    State * _state;
    uint _stateDimension;
    uint _stateDerivatives;
  public:

    virtual void notifyStateChanged()=0;
    virtual void notifyStateNeeded()=0;
    virtual void onStateAssigned(){}

  public:
    StatefulObject(uint dimension, uint derivatives):_stateDimension(dimension),_stateDerivatives(derivatives),_state(0){}
    StatefulObject():_stateDimension(0),_stateDerivatives(0),_state(0){}

    void assignState(State & state){
      _state = &state;
      state.resize(dimension(),derivatives());
      onStateAssigned();
    }
    void resizeState(uint dimension, uint derivatives){
      if(_stateDimension==dimension && _stateDerivatives ==derivatives)return;
      _stateDimension = dimension;
      _stateDerivatives = derivatives;
      if(!_state)return;
      state().resize(dimension,derivatives);
      assignState(state());
    }

    inline State & state(){return *_state;}
    inline uint derivatives(){return _stateDerivatives;}
    inline uint dimension(){return _stateDimension;}
  };

}
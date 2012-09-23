#include "StatefulObject.h"


using namespace nspace;

  StatefulObject::StatefulObject(uint dimension, uint derivatives):_stateDimension(dimension),_stateDerivatives(derivatives),_state(0){}
  StatefulObject::StatefulObject():_stateDimension(0),_stateDerivatives(0),_state(0){}

  void StatefulObject::assignState(State & state){
    _state = &state;
    state.resize(dimension(),derivatives());
    onStateAssigned();
  }
  void StatefulObject::resizeState(uint dimension, uint derivatives){
    if(_stateDimension==dimension && _stateDerivatives ==derivatives)return;
    _stateDimension = dimension;
    _stateDerivatives = derivatives;
    if(!_state)return;
    state().resize(dimension,derivatives);
    assignState(state());
  }
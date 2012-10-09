#pragma once

#include <simulation/ISimulationObject.h>
#include <simulation.state/State.h>

namespace nspace{
  // stateful object allows an object access to state.  the objects must implement notifyStateChanged,notifyStateNeeded
  class StatefulObject : public virtual ISimulationObject{
    TYPED_OBJECT(StatefulObject);
  private:
    State * _state;
    uint _stateDimension;
    uint _stateDerivatives;
  public:
    // is called when the state of the object was changed. clients can then 
    // set their objects internal data to the data specified by state()
    virtual void notifyStateChanged()=0;
    // is called when the state of this object is needed
    // implementing clients musst set the state of this object
    virtual void notifyStateNeeded()=0;
    // is called when the state * is changed and state() returns a new isntance
    virtual void onStateAssigned(){}    
    // access to the state
    inline State & state(){return *_state;}
  public:
    // returns true if this object has  a state assigned and thus state() can return a correct reference
    bool hasAssignedState()const;
    // instanciates stateful object  the dimension is the number of state this object requires and derivitaves is the number of 
    // of derivatives this object this object can supply 
    // you need to count the zeroth derivative . so for a constant this would result in 1 derivative. when the first derivative is available set to 2
    StatefulObject(uint dimension, uint derivatives);    
    // default constructor
    StatefulObject();
    // assign this object a state var
    void assignState(State * state);
    // resize this state
    void resizeState(uint dimension, uint derivatives);
    // returns the number of derivatives (including 0th derivative)
    inline uint derivatives(){return _stateDerivatives;}
    // returns the nubmer of available dimensions
    inline uint dimension(){return _stateDimension;}
  };

}
#pragma once
#include <core/patterns/Composite.h>
#include <simulation.state/StatefulObject.h>
namespace nspace{



  class CompositeStatefulObject : public virtual StatefulObject, public virtual Composite<StatefulObject>{
  public:

    void onStateAssigned(){
      uint currentOffset=0;
      foreachComponent([&currentOffset,this](StatefulObject* obj){
        uint currentDimension = obj->dimension();
        uint currentDerivatives = obj->derivatives();
        State * currentState = state().range(currentOffset,currentDimension,currentDerivatives);
        obj->assignState(*currentState);
        currentOffset+=currentDimension;
      });
    }
    void notifyStateChanged(){
      foreachComponent([](StatefulObject* obj){
        obj->notifyStateChanged();
      });
    }
    void notifyStateNeeded(){
      foreachComponent([](StatefulObject* obj){
        obj->notifyStateNeeded();
      });
    }
    void onAfterComponentAdded( StatefulObject* component ) 
    {
      uint d = derivatives();
      if(component->derivatives()>d)d= component->derivatives();
      resizeState(component->dimension()+dimension(),d);
      //component->assignState(*state().range(dimension()-component->dimension(),component->dimension(),component->derivatives()));
    }
    uint getMaximumDerivative(){
      uint result=0;
      foreachComponent([&result](StatefulObject* obj){
        if(result < obj->derivatives()){
          result = obj->derivatives();
        }
      });
      return result;
    }
    void onBeforeComponentRemoved( StatefulObject* component ) 
    {
      resizeState(getMaximumDerivative(),component->dimension()-dimension());
    }

  };
}
#pragma once
#include <simulation/core/ISimulationModule.h>
#include <simulation/core/CompositeSimulationObject.h>
#include <simulation/core/wrapper/Wrapper.h>
#include <simulation/core/Simulation.h>

namespace mbslib{	
class WrapperModule : public virtual Composite<Wrapper>, public virtual ISimulationModule {
public:
  ISimulationObject * wrapObject(ISimulationObject * object){
    CompositeSimulationObject * composite = new CompositeSimulationObject("WrappedObjects");
    // go through all wrappers and try to wrap the object.
    // if it works add it to the composite
    // then return the composite 
    // if object was not wrapped at all return 0
    foreachComponent([this, object, composite](Wrapper * wrapper){
      auto wrapped =  wrapper->wrap(object);
      if(wrapped){
        composite->addComponent(wrapped);
      }
    });
    if(composite->isEmpty()){
      //delete composite;
       return 0;
     }
     return composite;
  }
  
protected:
  void renounce(ISimulationObject * object){}
  void announce(ISimulationObject * object){
    auto wrappedObject = wrapObject(object);
    if(!wrappedObject)return ;
    simulation()->add(wrappedObject);
  }
};
}
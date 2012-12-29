#pragma once
#include <simulation/ISimulationModule.h>
#include <simulation/composites/CompositeSimulationObject.h>
#include <simulation.wrapper/Wrapper.h>
#include <simulation/Simulation.h>
#include <core.hub/CompositeHubObject.h>

namespace nspace{
  class WrapperModule : public virtual Composite<Wrapper>, public virtual ISimulationModule {
    TYPED_OBJECT(WrapperModule)
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
#pragma once
#include <simulation/ISimulationObject.h>
#include <core.hub/Module.h>
namespace nspace{
  /**
  * \brief
  *
  */

  class ISimulationModule:public virtual ISimulationObject, public virtual Module{
    TYPED_OBJECT(ISimulationModule);
  public:
    void announce(Object * object){
      auto obj = dynamic_cast<ISimulationObject*>(object);
      if(!obj)return;
      announce(obj);
    };
    void renounce(Object * object){
      auto obj = dynamic_cast<ISimulationObject*>(object);
      if(!obj)return;
      announce(obj);
    };
    virtual void announce(ISimulationObject * object)=0;
    virtual void renounce(ISimulationObject * object)=0;
  };
}

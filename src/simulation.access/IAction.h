#pragma once
#include <simulation.access/IComponent.h>
namespace nspace{
  class IAction : public virtual IComponent{
    REFLECTABLE_OBJECT(IAction);
  public:
    IAction(const std::string & name){setName(name);}
    virtual void execute()=0;
  };
}

#pragma once
#include <functional>

#include <core/patterns/Composite.h>
#include <simulation.access/IComponent.h>
#include <core.hub/CompositeHubObject.h>

namespace nspace{
  class IValue : public virtual IComponent{
    REFLECTABLE_OBJECT(IValue);
    SIMPLE_PROPERTY(const Type *, ValueType){};
  public:
    IValue():_ValueType(0){}
    virtual void get(void * value){};
    virtual void set(const void * value){};

    virtual bool isReadonly()const{return false;}
    virtual void toString(std::ostream & out)const{};
    virtual void fromString(std::istream & stream){};
  };

  class Group : public virtual IComponent, public virtual Composite<IComponent>{
    REFLECTABLE_OBJECT(Group);
  };
}

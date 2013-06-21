#pragma once

#include <core.reflection/dynamic/DynamicObjectImplementation.h>
#include <map>

namespace nspace{

class DynamicReflectedObjectImplementation : public DynamicObjectImplementation{
    reflect_type(DynamicObject);
    // stores wrapped object
    Argument data;
    // stores all created member values
    mutable std::map<std::string,std::shared_ptr<IModifiableValue>> _valueMap;
  public:
    DynamicReflectedObjectImplementation(Argument argument);
    std::shared_ptr<IModifiableValue> getMember(const std::string & name)override;
    std::shared_ptr<const IModifiableValue> getMember(const std::string & name)const override;
    MemberList getMethodNames()const override;
    MemberList getPropertyNames()const  override;
    Argument asArgument()override;
  };
}
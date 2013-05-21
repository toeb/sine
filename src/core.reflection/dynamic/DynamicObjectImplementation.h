#pragma once

#include <core.reflection/dynamic/DynamicObject.h>
namespace nspace{  

  
struct DynamicObjectImplementation{
  typedef DynamicObject::MemberList MemberList;
  virtual std::shared_ptr<IModifiableValue> getMember(const std::string  & name)=0;
  virtual MemberList getMemberNames();
  virtual Argument asArgument(){return Argument();}
};
}
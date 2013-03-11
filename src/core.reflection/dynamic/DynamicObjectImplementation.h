#pragma once

#include <core.reflection/dynamic/DynamicObject.h>
namespace nspace{  
struct DynamicObjectImplementation{
  typedef DynamicObject::MemberList MemberList;
  virtual Argument getMember(const std::string  & name)=0;
  virtual MemberList getMemberNames();
};
}
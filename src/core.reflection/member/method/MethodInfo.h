#pragma once
#include <core/reflection/MemberInfo.h>

namespace nspace{
  // MethodInfo represents a method of a class
  // TODO:  allow multiple arguments and return values
  // TODO get away from inheritance and use std::functions or something similar
  class MethodInfo : public virtual MemberInfo{
    TYPED_OBJECT(MethodInfo);
  public:
    // the call method must be implemented by a subclass
    virtual bool call(Object * object, void * arguments=0, void ** returnvalue=0)const=0;
    // the unsafe call method assumes object is a pointer to the concrete type
    virtual bool unsafeCall(void * object, void * arguments=0, void** returnvalue=0)const=0;
  };
}
#pragma once

#include <core/Object.h>
#include <core.reflection/member/method/MethodInfo.h>
#include <core.reflection/adapter/MemberAdapter.h>
#include <core.reflection/callable/Callable.h>

namespace nspace{
  class MethodAdapter : public Callable, public MemberAdapter{
    reflect_type(MethodAdapter);
    reflect_superclasses(Callable,MemberAdapter);

    typedef const MethodInfo * basic_property(MethodInfo);
  public:
    
    MethodAdapter();
    MethodAdapter(Argument object, const std::string & name);
    MethodAdapter(Argument object, const MethodInfo * method);    
  public:
    Argument callImplementation(const Arguments & args)override;
    bool isValid()const override;
  };
}

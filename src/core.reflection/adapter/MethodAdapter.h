#pragma once

#include <core/Object.h>
#include <core.reflection/member/method/MethodInfo.h>
#include <core.reflection/adapter/MemberAdapter.h>
#include <core.reflection/action/Action.h>

namespace nspace{
  class MethodAdapter : public virtual Action, public virtual MemberAdapter{
    TYPED_OBJECT(MethodAdapter);
    SIMPLE_PROPERTY(const MethodInfo *, MethodInfo){}
  public:
    MethodAdapter();
    MethodAdapter(Object * object, const std::string & name);
    MethodAdapter(Object * object, const MethodInfo * methodInfo);
  protected:
    void executeAction();
    bool call(void * arguments =0, void **returnvalue=0);
  };
}
#pragma once

#include <core.reflection/member/MemberInfo.h>
#include <core.reflection/type/Argument.h>
namespace nspace{
  class MemberAdapter{
    BASIC_PROPERTY(Argument,Owner,public,,onBeforeOwnerChanged();,onOwnerChanged());
  protected:
    MemberAdapter():_Owner(0){}
    virtual void onOwnerChanged(){}
    virtual void onBeforeOwnerChanged(){}
  };
}
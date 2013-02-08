#pragma once

#include <core/reflection/MemberInfo.h>
namespace nspace{
  class MemberAdapter : public virtual Object{
    TYPED_OBJECT(Object);
    BASIC_PROPERTY(Object*,Owner,public,,onBeforeOwnerChanged();,onOwnerChanged());
  protected:
    MemberAdapter():_Owner(0){}
    virtual void onOwnerChanged(){}
    virtual void onBeforeOwnerChanged(){}
  };
}
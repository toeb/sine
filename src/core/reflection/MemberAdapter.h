#pragma once

#include <core/reflection/MemberInfo.h>
namespace nspace{
  class MemberAdapter : public virtual Object{
    TYPED_OBJECT(Object);
    SIMPLE_PROPERTY(Object *, Owner){}
  protected:
    MemberAdapter():_Owner(0){}
  };

}
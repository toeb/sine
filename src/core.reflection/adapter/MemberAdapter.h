#pragma once

#include <core.reflection/member/MemberInfo.h>
namespace nspace{
  class MemberAdapter : public virtual Object{
  public:
    typedef MemberInfo::ObjectPointer ObjectPointer;
    DS_CLASS(MemberAdapter);
    //ConstTypePtr basic_property(OwningType);
    BASIC_PROPERTY(ObjectPointer,Owner,public,,onBeforeOwnerChanged();,onOwnerChanged());
  protected:
    MemberAdapter():_Owner(0){}
    MemberAdapter(void * owner, ConstTypePtr type){}
    template<typename T>
    MemberAdapter(T * owner):_Owner(owner->getType()), {}
    virtual void onOwnerChanged(){}
    virtual void onBeforeOwnerChanged(){}
  };
}
#pragma once

#include <core.reflection/member/MemberInfo.h>
namespace nspace{
  class MemberAdapter : public virtual Object{
    extensible_property_class
  public:
    typedef MemberInfo::ObjectPointer ObjectPointer;
    DS_CLASS(MemberAdapter);
    //ConstTypePtr basic_property(OwningType);
    //BASIC_PROPERTY(ObjectPointer,Owner,public,,onBeforeOwnerChanged();,onOwnerChanged());
    ObjectPointer extensible_property(Owner);
    ConstTypePtr basic_property(OwnerType);


    before_set(Owner){
      onBeforeOwnerChanged();
    }
    after_set(Owner){
      onOwnerChanged();
    }
    
  protected:
    MemberAdapter():_Owner(0),_OwnerType(0){}
    template<typename T>
    MemberAdapter(T * owner):_Owner(owner),_OwnerType(owner->getType()) {
      onOwnerChanged();
    }
    MemberAdapter(void * owner, ConstTypePtr type){}
    virtual void onOwnerChanged(){}
    virtual void onBeforeOwnerChanged(){}
  };
}
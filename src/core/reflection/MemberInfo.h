#pragma once
#include <core/Object.h>

namespace nspace{
  class MemberInfo : public virtual Object{
    TYPED_OBJECT(MemberInfo);
    
    SIMPLE_PROPERTY(std::string, Name){if(getDisplayName()!="")return; setDisplayName(newvalue);}
    REFERENCE_PROPERTY(std::string, Name);

    SIMPLE_PROPERTY(bool, IsVisible){}
    SIMPLE_PROPERTY(Type *, OwningType ){};

    
    SIMPLE_PROPERTY(std::string, Description){}
    SIMPLE_PROPERTY(std::string, DisplayName){}
    SIMPLE_PROPERTY(std::string, GroupName){}
  public:
    MemberInfo():
      _IsVisible(true),
      _OwningType(0)
    {}
  };
}

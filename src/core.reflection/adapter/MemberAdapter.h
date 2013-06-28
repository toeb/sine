#pragma once

#include <core.reflection/member/MemberInfo.h>
#include <core.reflection/type/Argument.h>
namespace nspace{
  class MemberAdapter{
    reflect_type_declaration(nspace::MemberAdapter);    
    typedef Argument extensible_property(Owner);
  protected:
    MemberAdapter();
    MemberAdapter(Argument owner);
    virtual auto before_set(Owner);
    virtual auto after_set(Owner);

  };
}
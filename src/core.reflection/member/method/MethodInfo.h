#pragma once
#include <core.reflection/member/MemberInfo.h>
#include <core.reflection/type/Argument.h>
#include <core.reflection/callable/ArgumentInfo.h>
#include <core.reflection/callable/CallableInfo.h>
namespace nspace{


  class MethodInfo : public MemberInfo, public virtual CallableInfo{
  public:
    virtual const Type  * getType()const;
    static bool initializeType();

    propdef std::string basic_property(PureName);
  };
}




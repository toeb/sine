#pragma once

#include <core.reflection/callable/ArgumentInfo.h>
namespace nspace{
  template<typename ArgumentType, unsigned int ArgumentIndex>
  class TypedArgumentInfo : public ArgumentInfo{
  public:
    TypedArgumentInfo();
  };
}

namespace nspace{
  template<typename ArgumentType, unsigned int ArgumentIndex>
  TypedArgumentInfo<ArgumentType,ArgumentIndex>::TypedArgumentInfo(){
    setIndex(ArgumentIndex);
    setArgumentType(TypeInfo<ArgumentType>::instance());
    setName(DS_INLINE_STRING("a"<<ArgumentIndex));
  }
}
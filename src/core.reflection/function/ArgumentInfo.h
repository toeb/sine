#pragma once
#include <config.h>

namespace nspace{

  /// represents an argument of a method signature
  class ArgumentInfo : public AttributeTarget{
  public:
    propdef unsigned int basic_property(Index);
    propdef std::string basic_property(Name);
    propdef std::shared_ptr<const Type> basic_property(ArgumentType);
    propdef Argument basic_property(DefaultValue);
  };

  template<typename ArgumentType, unsigned int ArgumentIndex>
  class TypedArgumentInfo : public ArgumentInfo{
  public:
    TypedArgumentInfo(){
      setIndex(ArgumentIndex);
      setArgumentType(TypeInfo<ArgumentType>::instance());
      setName(DS_INLINE_STRING("a"<<ArgumentIndex));
    }
  };

}
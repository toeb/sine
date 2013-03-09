#pragma once
#include <core.reflection/member/property/PropertyInfo.h>
#include <core.serialization/Serialization.h>
namespace nspace{
  template<typename ClassType>
  struct TypedPropertyInfo:public PropertyInfo{
    TypedPropertyInfo(const std::string & name, const MethodInfo * getter, const MethodInfo * setter):PropertyInfo(name,getter,setter){
      setOwningType(type_of<ClassType>());     
    }
  };
}

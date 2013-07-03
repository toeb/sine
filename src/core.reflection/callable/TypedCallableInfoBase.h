#pragma once
#include <core.reflection/callable/CallableInfo.h>

namespace nspace{

  template<typename TCallable,typename TReturnType>
  struct TypedCallableInfoBase : public nspace::CallableInfo{
    typedef TCallable callable_type;
    typedef TReturnType return_type;
    propdef callable_type basic_property(Callable);
    property_reference(Callable);

  protected:
    TypedCallableInfoBase(callable_type callable):
      CallableInfo(),
      _Callable(callable)
    {
      setReturnType(type_of<return_type>());
    }
  };

}
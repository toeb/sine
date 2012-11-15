#pragma once

#include <core/Object.h>
#include <core/reflection/MethodInfo.h>
namespace nspace{
  class MethodAdapter : public Object{
    Object * _object;
    const MethodInfo & _methodInfo;
  public:
    const MethodInfo & methodInfo()const;
    Object * object();
    MethodAdapter(Object * object, const MethodInfo & method);
    bool call(void * arguments =0, void **returnvalue=0);

  };
}
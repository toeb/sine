#pragma once
#include <core.reflection/callable/CallableInfo.h>
namespace nspace{

  class StaticMethodInfo : public CallableInfo{
  public:
    virtual const Type* getType()const override;
    static bool initializeType();
    

  };

  template<typename TMethod>
  class TypedStaticMethodInfo:public StaticMethodInfo{
  public:

  };

}
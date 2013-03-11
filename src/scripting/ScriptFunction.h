#pragma once

#include <core.reflection/callable/Callable.h>
#include <core.reflection/callable/CallableFunctor.h>
#include <core.reflection/dynamic/DynamicCallableImplementation.h>
namespace nspace{
  




  // template implementation  
  template<typename TCallable>
  struct ScriptCallableImplementationCallableFunctor:public DynamicCallableImplementation{
    CallableFunctor<TCallable> callable;
    ScriptCallableImplementationCallableFunctor(CallableFunctor<TCallable> callable):callable(callable){}

    bool isValid() const override final{
      return callable.isValid();
    }
    Argument callImplementation(const Arguments & args) override final{
      return callable.callImplementation(args);
    }
    Argument callImplementation(const Arguments & args) const override final{
      return callable.callImplementation(args);
    }
  };

  template<typename TCallable> DynamicCallable::DynamicCallable(CallableFunctor<TCallable> callable):implementation(new ScriptCallableImplementationCallableFunctor<TCallable>(callable)){}

  
}
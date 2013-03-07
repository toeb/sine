#pragma once

#include <core.reflection/callable/Callable.h>
#include <core.reflection/callable/CallableFunctor.h>

namespace nspace{


  struct ScriptFunctionImplementation;

  struct ScriptFunction : public Callable{
    reflect_type(ScriptFunction);
  public:
    ScriptFunction(Callable * callable);
    ScriptFunction(Callable & callable);
    ScriptFunction(std::shared_ptr<Callable> callable);
    ScriptFunction(std::shared_ptr<ScriptFunctionImplementation> impl);
    ScriptFunction();

    template<typename TCallable> ScriptFunction(CallableFunctor<TCallable> callable);

    std::shared_ptr<ScriptFunctionImplementation> impl;

    bool isValid()const override final;
    Argument callImplementation(const Arguments &args)override final;
  };

  //
  struct ScriptFunctionImplementation : public Callable{
    virtual bool isValid()const=0;
    virtual Argument callImplementation(const Arguments &args)=0;
  };


  // template implementation  
  template<typename TCallable>
  struct ScriptCallableImplementationCallableFunctor:public ScriptFunctionImplementation{
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

  template<typename TCallable> ScriptFunction::ScriptFunction(CallableFunctor<TCallable> callable):impl(new ScriptCallableImplementationCallableFunctor<TCallable>(callable)){}


}
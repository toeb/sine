#include "ScriptFunction.h"

using namespace nspace;

struct ScriptCallableImplementationSmartPointer:public ScriptFunctionImplementation{
  std::shared_ptr<Callable> callable;
  ScriptCallableImplementationSmartPointer(std::shared_ptr<Callable> callable):callable(callable){}
  bool isValid() const override final{
    return callable->isValid();
  }
  Argument callImplementation(const Arguments & args) override final{
    return callable->callImplementation(args);
  }
  Argument callImplementation(const Arguments & args) const override final{
    return callable->callImplementation(args);
  }
};

struct ScriptCallableImplementationRawPointer:public ScriptFunctionImplementation{
  Callable * callable;
  ScriptCallableImplementationRawPointer(Callable * callable):callable(callable){}
  bool isValid() const override final{
    return callable->isValid();
  }
  Argument callImplementation(const Arguments & args) override final{
    return callable->callImplementation(args);
  }
  Argument callImplementation(const Arguments & args) const override final{
    return callable->callImplementation(args);
  }
};


ScriptFunction::ScriptFunction(std::shared_ptr<Callable> callable):impl(new ScriptCallableImplementationSmartPointer(callable)){}
ScriptFunction::ScriptFunction(Callable * callable):impl(new ScriptCallableImplementationRawPointer(callable)){}
ScriptFunction::ScriptFunction(Callable & callable):impl(new ScriptCallableImplementationRawPointer(&callable)){}

ScriptFunction::ScriptFunction(std::shared_ptr<ScriptFunctionImplementation> impl):impl(impl){}
ScriptFunction::ScriptFunction(){}


bool ScriptFunction::isValid()const {return (bool)impl&&impl->isValid();}
Argument ScriptFunction::callImplementation(const Arguments &args){return impl->callImplementation(args);}
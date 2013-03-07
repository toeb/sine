#pragma once

#include <scripting.h>

#include <map>
namespace nspace{
  struct Module;
  struct PythonType;
  struct ScriptFunctionImplementation : public Callable{

    virtual bool isValid()const=0;
    virtual Argument callImplementation(const Arguments &args)=0;
  };

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
  
 

  struct ScriptFunction : public Callable{
    reflect_type(ScriptFunction);
  public:
    ScriptFunction(std::shared_ptr<Callable> callable):impl(new ScriptCallableImplementationSmartPointer(callable)){}
    ScriptFunction(Callable * callable):impl(new ScriptCallableImplementationRawPointer(callable)){}
    ScriptFunction(Callable & callable):impl(new ScriptCallableImplementationRawPointer(&callable)){}
    template<typename TCallable> ScriptFunction(CallableFunctor<TCallable> callable):impl(new ScriptCallableImplementationCallableFunctor<TCallable>(callable)){}
    ScriptFunction(std::shared_ptr<ScriptFunctionImplementation> impl):impl(impl){}
    ScriptFunction(){}
    std::shared_ptr<ScriptFunctionImplementation> impl;
 
    bool isValid()const override{return (bool)impl&&impl->isValid();}
    Argument callImplementation(const Arguments &args)override{return impl->callImplementation(args);}
  };
  class PythonScriptMachine : public VirtualScriptMachine{
    static size_t instances;
    std::map<std::string ,std::shared_ptr<Module>> modules;
    std::vector<PythonType*> types;
  public:
    PythonScriptMachine();
    ~PythonScriptMachine() override;
    void initStaticTypes();
    bool registerType(const Type * type)override;
    bool loadStream(std::istream & stream)override;
    bool registerObject(const std::string & variablename, Argument argument);


    bool setVariable(const std::string & name, Argument argument);
    Argument getVariable(const std::string & name,const Type* type=0);

    template<typename T> bool getVariable(T & val, const std::string & name){
      auto arg = getVariable(name, typeof(T));
      if(!arg.isValid())return false;
      val = (T)arg;
      return true;
    }
    template <typename T> T getVariable(const std::string & name){
      T  val;
      getVariable<T>(val,name);
      return val;  
    }

    ScriptFunction getFunction(const std::string & name){
      return getVariable<ScriptFunction>(name);
    }
    bool setFunction(const std::string & name, ScriptFunction func ){
     return  setVariable(name,func);
    }
    template <typename TFunctor>bool setFunctor(const std::string & name, TFunctor func){
      return setFunction(name, make_callable(func));
    }
    


  };


}
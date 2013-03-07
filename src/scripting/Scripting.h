#pragma once

#include <core.logging.h>
#include <scripting/ScriptFunction.h>
namespace nspace{

  class VirtualScriptMachine : public Log{
    reflect_type(VirtualScriptMachine);
    reflect_superclasses(Log);

    PROPERTYSET(std::shared_ptr<Object>, ManagedObjects,{},{});
  public:
    virtual bool registerType(const Type * type);
    virtual bool setVariable(const std::string & name, Argument argument);
    virtual Argument getVariable(const std::string & name,const Type* type=0);
    template<typename T> bool getVariable(T & val, const std::string & name);
    template <typename T> T getVariable(const std::string & name);
    virtual ScriptFunction getFunction(const std::string & name);
    virtual bool setFunction(const std::string & name, ScriptFunction func );
    template <typename TFunctor>bool setFunctor(const std::string & name, TFunctor func);



    virtual bool loadStream(std::istream & stream);
    bool loadString(const std::string & script);
    bool loadFile(const std::string & filename);


  };


}


//template implemenation

namespace nspace{

  template<typename T> bool VirtualScriptMachine::getVariable(T & val, const std::string & name){
    auto arg = getVariable(name, typeof(T));
    if(!arg.isValid())return false;
    val = (T)arg;
    return true;
  }
  template <typename T> T VirtualScriptMachine::getVariable(const std::string & name){
    T  val;
    getVariable<T>(val,name);
    return val;  
  }

  template <typename TFunctor>bool VirtualScriptMachine::setFunctor(const std::string & name, TFunctor func){
    return setFunction(name, make_callable(func));
  }


}


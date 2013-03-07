#pragma once

#include <scripting.h>

#include <map>
namespace nspace{
  struct Module;
  struct PythonType;
  struct ScriptFunctionImplementation{

    virtual bool isValid()const=0;
    virtual Argument call(std::vector<Argument> &args)=0;
  };
  struct ScriptFunction{
    reflect_type(ScriptFunction);
  public:
    ScriptFunction(std::shared_ptr<ScriptFunctionImplementation> impl):impl(impl){}
    ScriptFunction(){}
    std::shared_ptr<ScriptFunctionImplementation> impl;
    Argument operator()(){
      return operator()(std::vector<Argument>());
    }
    template<typename TContainer> Argument operator()(TContainer & container){
      std::vector<Argument> vec;
      for(auto it = std::begin(container); it!=std::end(container); it++){
        vec.push_back(*it);
      }
      return call(vec);
    }
    bool isValid(){return (bool)impl&&impl->isValid();}
    Argument call(std::vector<Argument> &args){return impl->call(args);}
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



  };


}
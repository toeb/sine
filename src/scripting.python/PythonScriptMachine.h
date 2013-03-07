#pragma once

#include <scripting.h>

#include <map>
namespace nspace{
  struct Module;
  struct PythonType;
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
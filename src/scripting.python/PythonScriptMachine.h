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
};


}
#pragma once

#include <scripting.h>


namespace nspace{
  
class PythonScriptMachine : public VirtualScriptMachine{
  static size_t instances;
public:
  PythonScriptMachine();
  ~PythonScriptMachine() override;
  void initStaticTypes();
  bool registerType(const Type * type)override;
  bool loadStream(std::istream & stream)override;
};


}
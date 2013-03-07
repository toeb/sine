#pragma once

#include <scripting.h>



namespace nspace{
class PythonScriptMachine : public VirtualScriptMachine{
  REFLECTABLE_OBJECT(PythonScriptMachine);
  
};
}
#pragma once
#include <core/patterns/Singleton.h>

#include <scripting.python/PythonUtilities.h>
#include <scripting.python/PythonScriptMachine.h>
namespace nspace{

  struct PythonCallable : public PyObject{
    DynamicCallable callable;
    PythonCallable(DynamicCallable callable):callable(callable){
    }

  };
  struct PythonCallableType :  PyTypeObject{
    SINGLETON(PythonCallableType);
  };

}
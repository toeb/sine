#pragma once

#include <scripting.python/PythonScriptMachine.h>
#include <Python.h>

namespace nspace{

struct PythonFunction : public ScriptFunctionImplementation{
  PyObject * func;
  PythonFunction(PyObject * func);

  bool isValid()const override;
  ~PythonFunction();
  Argument call(std::vector<Argument> & args)override;
};

}
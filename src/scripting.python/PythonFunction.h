#pragma once

#include <scripting.python/PythonScriptMachine.h>
#include <Python.h>

namespace nspace{

struct PythonFunction : public DynamicCallableImplementation{
  PyObject * func;
  PythonFunction(PyObject * func);  
  ~PythonFunction() override final;
  bool isValid()const override final;
  Argument callImplementation(const Arguments & args)override final;
};

}
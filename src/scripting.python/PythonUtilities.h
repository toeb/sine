#pragma once
// if debug is defined then some more unlinkable functions will be added
// so i disable the debug flag for python.h
// // comment out following lines under windows
// pyconfig.h 327
// pyconfig.h 329 
// pyconfig.h 331
// pyconfig.h 371
// 
#include <Python.h>


#include <core.reflection.h>

namespace nspace{
  struct PythonType;
  struct PythonModule;
  std::string formatModuleName(const ScopeInfo * ns);
  std::string formatModuleName(const Type * type);
  Argument pythonObjectToArgument(PyObject * object, const Type * type);
  PyObject * pythonObjectFromArgument(Argument arg);
  PythonType * getPythonType(const Type * type);
  PyObject * requireModule(const std::string & name);
}
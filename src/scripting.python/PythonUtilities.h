#pragma once
// if debug is defined then some more unlinkable functions will be added
// so i disable the debug flag for python.h
#include <Python.h>

#include <core.reflection.h>

namespace nspace{
  

Argument pythonObjectToArgument(PyObject * object, const Type * type);
PyObject * pythonObjectFromArgument(Argument arg);
}
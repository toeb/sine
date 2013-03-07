#pragma once
// if debug is defined then some more unlinkable functions will be added
// so i disable the debug flag for python.h
#ifdef _DEBUG
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif

#include <core.reflection.h>
namespace nspace{

Argument pythonObjectToArgument(PyObject * object, const Type * type);
PyObject * pythonObjectFromArgument(Argument arg);
}
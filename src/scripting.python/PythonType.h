#pragma once

#include <core.reflection.h>

#include <scripting.python/PythonUtilities.h>

namespace nspace{

struct PythonType : public PyTypeObject{
  PyObject * construct(PyObject *args, PyObject *kwds);
 static void       destruct(void * object);
  static PyObject * getProperty(PyObject* pobject, PyObject * name );
  static int        setProperty(PyObject * object, PyObject * , PyObject* value);
 static  PyObject * stringRepresentation(PyObject * object);

  PythonType(const Type* type);
  const Type * type;
};
}
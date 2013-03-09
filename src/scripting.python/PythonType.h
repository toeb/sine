#pragma once

#include <core.reflection.h>

#include <scripting.python/PythonUtilities.h>

namespace nspace{

  struct PythonType : public PyTypeObject{
    PyObject * construct(PyObject *args, PyObject *kwds);
    static void destruct(void * object);



    static PyObject * getAttribute(PyObject* pobject, PyObject * name );
    static int setAttribute(PyObject * object, PyObject * name, PyObject* value);


    PythonType(const Type* type);
    const Type * type;
  };
}
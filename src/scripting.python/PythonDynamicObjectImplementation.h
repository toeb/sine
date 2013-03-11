#pragma once
#include <core.reflection/dynamic/DynamicObjectImplementation.h>
#include <Python.h>
namespace nspace{

  class PythonDynamicObject : public DynamicObjectImplementation{
    PyObject * object;
  public:
    PythonDynamicObject(PyObject * pyObject);
    ~PythonDynamicObject();

    Argument getMember(const std::string & name)override final;
    MemberList getMemberNames() override final;
  };


}
#pragma once
#include <core.reflection/type/Argument.h>
#include <map>
#include <scripting.python/PythonUtilities.h>


namespace nspace{
struct PythonObject:public PyObject{
  PythonObject(Argument object):object(object){}
  //converts a PyObject to a PythonObject (int or
  PythonObject(PyObject * pObject){

  }


  Argument object;
  std::map<std::string, std::shared_ptr<MemberAdapter>> members;


  PyObject* getAttribute(PyObject * name);
  int setAttribute(PyObject * name, PyObject * value);

private:
  std::shared_ptr<MemberAdapter> getMember(PyObject * pname);


};
}
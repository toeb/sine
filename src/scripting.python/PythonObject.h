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
  // converts PythonObject to a pyObject * 
  operator PyObject * (){

  }

  Argument object;
  std::map<std::string, std::shared_ptr<MemberAdapter>> members;


  PyObject* getMember(const std::string & name);
  
};
}
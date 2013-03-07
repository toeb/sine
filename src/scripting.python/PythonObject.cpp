#include "PythonObject.h"

#include <scripting.python/PythonMethodAdapter.h>
using namespace nspace;



PyObject* PythonObject::getMember(const std::string & name){
  auto it = members.find(name);
  std::shared_ptr<MemberAdapter> member;
  if(it==members.end()){

    auto methodInfo= this->object.type->getMethod(name);
    if(methodInfo){
      member= std::shared_ptr<MethodAdapter>(new MethodAdapter(object,methodInfo));
    }
    auto propertyInfo=this->object.type->getProperty(name);
    if(propertyInfo){
      member = std::shared_ptr<PropertyAdapter>(new PropertyAdapter(object,propertyInfo));
    }
    if((bool)member){
      members[name]=member;
    }
    // create member
  }else{
    member = it->second;
  }

  auto method = std::dynamic_pointer_cast<MethodAdapter>(member);
  if((bool)method){

    auto module = PyImport_AddModule("ds.statictypes");
    auto dict = PyModule_GetDict(module);
    auto t = (PythonCallableType*) PyDict_GetItemString(dict,"MethodWrapper");
    auto c= PyObject_New(PythonCallable,t);
    new(c) PythonCallable(ScriptFunction(method));
    return c;
  }
  auto property = std::dynamic_pointer_cast<PropertyAdapter>(member);
  if((bool)property){

  }
  return Py_BuildValue("");


}
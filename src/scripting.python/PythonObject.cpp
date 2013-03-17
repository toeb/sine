#include "PythonObject.h"

#include <scripting.python/PythonMethodAdapter.h>
using namespace nspace;



std::shared_ptr<MemberAdapter> PythonObject::getMember(PyObject * pname){
  // extract name
  std::string name = PyUnicode_AsUTF8(pname);

  // search for member if it does not exist in obeject search type to find it and create
  auto it = members.find(name);
  std::shared_ptr<MemberAdapter> member;
  if(it==members.end()){    
    // try to create member
    auto methodInfo= object.type->getMethod(name);
    if(methodInfo){
      member= std::shared_ptr<MethodAdapter>(new MethodAdapter(object,methodInfo));
    }
    auto propertyInfo=object.type->getProperty(name);
    if(propertyInfo){
      member = std::shared_ptr<PropertyAdapter>(new PropertyAdapter(object,propertyInfo));
    }
    // even if member is not found set the emtpy pointer. 
    // this will cause the searchprocedure to be only run once    
    members[name]=member;
  }else{
    member = it->second;
  }
  return member;
}

int PythonObject::setAttribute(PyObject * pname, PyObject *value){
  // get the member
  auto member = getMember(pname);

  // if there is a no member do default python set attribute
  if(!(bool)member){
    return PyObject_GenericSetAttr(this,pname,value);
  }

  // if member is a property set the property
  auto property = std::dynamic_pointer_cast<PropertyAdapter>(member);
  if((bool)property){
    auto argument = pythonObjectToArgument(value,property->getValueType());
    property->set(argument);
    return 0;
  }

  auto method = std::dynamic_pointer_cast<MethodAdapter>(member);
  // if member is a method
  if((bool)method){
    // todo need to set attributeerror 
    // return failure
    return -1;
  }

  return 0;
}

PyObject* PythonObject::getAttribute(PyObject * pname){
  // get the member
  auto member = getMember(pname);
  
  // if no member exists use default function to get value (look up value in dict)
  if(!(bool)member){
    return PyObject_GenericGetAttr(this,pname);
  }

  // else there is a member 

  // if member is a method return the method adapter
  // which is callable
  auto method = std::dynamic_pointer_cast<MethodAdapter>(member);
  if((bool)method){
    return pythonObjectFromArgument(DynamicCallable(method));
  }

  // if member is a property return the properties value
  auto property = std::dynamic_pointer_cast<PropertyAdapter>(member);
  if((bool)property){
    return pythonObjectFromArgument(property->get());
  }

  // return  to show everything failed  
  // todo:  raise attribute exception
  return 0;


}
#include "PythonDynamicObjectImplementation.h"

#include <Python.h>
#include <scripting.python/PythonUtilities.h>
using namespace nspace;
using namespace std;



PythonDynamicObject::PythonDynamicObject(PyObject * pyObject):object(pyObject){
  Py_IncRef(object);
}
PythonDynamicObject::~PythonDynamicObject(){
  Py_DecRef(object);
}

Argument PythonDynamicObject::getMember(const std::string & name){    

  auto attr = PyObject_GetAttrString(object,name.c_str());
  if(!attr)return Argument();
  return pythonObjectToArgument(attr,0);
}
PythonDynamicObject::MemberList PythonDynamicObject::getMemberNames() {
  MemberList result;
  auto dictPtr = _PyObject_GetDictPtr(object);
  if(dictPtr==0)return result;
  if(*dictPtr==0)return result;
  auto dict = *dictPtr;
  auto keyList = PyDict_Keys(dict);
  auto n= PyList_Size(keyList);
  for(Py_ssize_t i=0; i < n; i++){
    auto key = PyList_GetItem(keyList,i);
    std::string name = PyUnicode_AsUTF8(key);

  }
}
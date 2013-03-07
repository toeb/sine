#include "PythonUtilities.h"

#include <scripting.python/PythonObject.h>
#include <scripting.python/PythonType.h>
#include <scripting.python/PythonScriptMachine.h>
using namespace nspace;


Argument nspace::pythonObjectToArgument(PyObject * object, const Type * type){
  if(type==typeof(int)){
    if(!PyNumber_Check(object))return Argument();
    auto l = PyNumber_Long(object);
    
    auto ll = (int)PyLong_AsLong(l);
    return ll;
  }
  if(type==typeof(std::string)){
    if(!PyUnicode_Check(object))return Argument();

    auto s = PyUnicode_AsUTF8(object);    
    std::string s2(s);
    return s2;
  }
  
  auto t = reinterpret_cast<PyTypeObject*>(PyObject_Type(object));
  auto t2 =static_cast<PythonType*>(t);
  auto o = static_cast<PythonObject*>(object);
  auto arg = o->object;
  return arg;

}


PyObject * nspace::pythonObjectFromArgument(Argument arg){
  if(arg.type==typeof(int)){
    return Py_BuildValue("i",(int)arg);
  }




  return 0;
}

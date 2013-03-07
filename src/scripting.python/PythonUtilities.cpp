#include "PythonUtilities.h"

#include <scripting.python/PythonObject.h>
#include <scripting.python/PythonType.h>
#include <scripting.python/PythonScriptMachine.h>
#include <scripting.python/PythonVariable.h>
#include <scripting.python/PythonFunction.h>
#include <scripting.python/PythonMethodAdapter.h>
using namespace nspace;




Argument nspace::pythonObjectToArgument(PyObject * object, const Type * type){
  
  if(type==typeof(int)||type==0&&PyLong_CheckExact(object)){
    if(!PyNumber_Check(object))return Argument();
    auto l = PyNumber_Long(object);    
    auto ll = (int)PyLong_AsLong(l);
    return ll;
  }
  if(type==typeof(std::string)||PyObject_TypeCheck(object,&PyUnicode_Type)){
    if(!PyUnicode_Check(object))return Argument();

    auto s = PyUnicode_AsUTF8(object);    
    std::string s2(s);
    return s2;
  }

  if(type==typeof(ScriptFunction)){
    ScriptFunction s(std::static_pointer_cast<Callable>(std::shared_ptr<PythonFunction>(new PythonFunction(object))));
    return s;
  }


  
  auto t = reinterpret_cast<PyTypeObject*>(PyObject_Type(object));
  if(!t)return Argument();
  auto t2 =static_cast<PythonType*>(t);
  if(!t2)return Argument();
  if(!t2->type){
    return Argument();    
  }
  auto o = static_cast<PythonObject*>(object);
  if(!o)return Argument();
  auto arg = o->object;
  return arg;

}


PyObject * nspace::pythonObjectFromArgument(Argument arg){
  if(!arg.isValid()){
    return 0;
  }
  
  if(arg.type==0){
    return Py_BuildValue("");
  }
  if(arg.type==typeof(int)){
    return Py_BuildValue("i",(int)arg);
  }
  if(arg.type==typeof(std::string)){
    return PyUnicode_FromString(arg.cast<std::string>()->c_str());
  }
  if(arg.type==typeof(ScriptFunction)){
    auto module = PyImport_ImportModule("ds.statictypes");
    auto dict = PyModule_GetDict(module);
    auto methodType= (PythonCallableType*) PyDict_GetItemString(dict,"MethodWrapper");
    auto pcallable = PyObject_New(PythonCallable,methodType);
    new (pcallable) PythonCallable((ScriptFunction)arg);
    return pcallable;
  }

  auto ns = stringtools::replace(arg.type->getNamespace()->getFullyQualifiedName(),"::",".");
  auto name = arg.type->getName();



  auto module = PyImport_ImportModule(name.c_str());
  if(!module)return 0;
  auto dict = PyModule_GetDict(module);
  if(!dict)return 0;  
  auto val = PyDict_GetItemString(dict,name.c_str());
  if(!val)return 0;




  return 0;
}
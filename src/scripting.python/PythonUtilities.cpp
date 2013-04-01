#include "PythonUtilities.h"

#include <scripting.python/PythonObject.h>
#include <scripting.python/PythonType.h>
#include <scripting.python/PythonScriptMachine.h>
#include <scripting.python/PythonVariable.h>
#include <scripting.python/PythonFunction.h>
#include <scripting.python/PythonMethodAdapter.h>

#include <scripting.python/PythonDynamicObjectImplementation.h>
#include <scripting.python/PythonModule.h>
using namespace nspace;


using namespace std;
PyObject * nspace::requireModule(const std::string & name){
  using namespace stringtools;
  auto parts = split(name,'.');

  if(parts.size()==1 && parts[0]=="")return PyImport_AddModule("__main__");

  stringstream stream;
  auto part = begin(parts);
  PyObject * result = 0;
  while(true){
    if(part==end(parts))break;
    stream << *part;
    auto current = stream.str();
    result =PyImport_AddModule(current.c_str());
    stream<<".";
    part++;
  }
  return result;
}





std::string nspace::formatModuleName(const ScopeInfo * scope){
  if(!scope)return "__main__";
  auto result = scope->formatName("_");
  if(stringtools::startsWith(result,"_"))result = result.substr(1);
  if(result=="")return "__main__";
  return result;
}

std::string nspace::formatModuleName(const Type * type){
  if(!type)return "__main__";
  return formatModuleName(type->getNamespace());
}

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

  if(type==typeof(DynamicCallable)){
    DynamicCallable s(std::static_pointer_cast<Callable>(std::shared_ptr<PythonFunction>(new PythonFunction(object))));
    return s;
  }  
  
  if(object->ob_type->tp_name==std::string("method")){
    DynamicCallable s(std::static_pointer_cast<Callable>(std::shared_ptr<PythonFunction>(new PythonFunction(object))));
    return s;
  }

  auto pythonType = reinterpret_cast<PyTypeObject*>(PyObject_Type(object));

  // illegal type
  if(!pythonType)return Argument();
  

  
  // all wrapper types share tp_free function (a kind of hack for getting correct type
  // so if tp_free is not equal to PythonTypes destruct function i can assume its a python built in type (or at least a type not managed by my code)
  if(&PythonType::destruct!=pythonType->tp_free){
    // for non wrapped types:
    auto pythonDynamicObject = std::shared_ptr<PythonDynamicObject>(new PythonDynamicObject(object));
    return DynamicObject(pythonDynamicObject);
  }
  
  // else it's a type wrapper and I can just return the internal stored object
  auto wrappedType =static_cast<PythonType*>(pythonType);
  if(!wrappedType)return Argument();
  if(!wrappedType->type)return Argument();

  auto pythonObject = static_cast<PythonObject*>(object);
  if(!pythonObject)return Argument();
  return pythonObject->object;

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
  if(arg.type==typeof(DynamicCallable)){
    auto module = PyImport_ImportModule("cppinterop");
    if(!module){
      std::cerr<<"could not find module cppinterop"<<std::endl;
      return 0;
    }
    auto dict = PyModule_GetDict(module);
    auto methodType= (PythonCallableType*) PyDict_GetItemString(dict,"MethodWrapper");
    auto pcallable = PyObject_New(PythonCallable,methodType);
    new (pcallable) PythonCallable((DynamicCallable)arg);
    return pcallable;
  }


  auto ptype = getPythonType(arg.type);
  auto pobject = PyObject_New(PythonObject,ptype);
  new (pobject) PythonObject(arg);
  return pobject;
}
PythonType * nspace::getPythonType(const Type * type){
  // alternatively this code look in python script machines types vector
  auto ns = formatModuleName(type);
  auto name = type->getName();
  auto module = PyImport_ImportModule(ns.c_str());
  if(!module)return 0;
  auto dict = PyModule_GetDict(module);
  if(!dict)return 0;  
  auto val = PyDict_GetItemString(dict,name.c_str());
  if(!val)return 0;  
  return (PythonType*)val;
};

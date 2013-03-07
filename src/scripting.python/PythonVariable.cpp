#include "PythonVariable.h"
#include <scripting.python/PythonUtilities.h>
#include <core.utility/StringTools.h>
#include <scripting.python/PythonType.h>
#include <scripting.python/PythonObject.h>

using namespace nspace;
using namespace std;

PythonVariable::PythonVariable(const std::string  &name){
  auto nameParts = stringtools::split(name, '.');
  module = "__main__";
  this->name=nameParts[nameParts.size()-1];
  // get namespace / module string
  if(nameParts.size()>1){
    stringstream ss;
    for(int i=0; i < nameParts.size()-1;i++){
      ss << nameParts[i];
      ss << ".";
    }
    module = ss.str();
    module = module.substr(0,module.size()-1);
  }
}



PythonVariable  & PythonVariable::operator = (Argument argument){
  return *this;
}

bool PythonVariable::assign(Argument argument){
  PyObject * targetModule = PyImport_AddModule(this->module.c_str());
  if(!targetModule)return false;

  auto pyObject= pythonObjectFromArgument(argument);
  if(!pyObject){
    auto ns = argument.type->getNamespace()->getFullyQualifiedName();
    ns = stringtools::replace(ns,"::",".");
    auto tname=argument.type->getName();

    auto mod = PyImport_ImportModule(ns.c_str());
    if(!mod)return false;

    auto dict = PyModule_GetDict(mod);
    auto ptype=(PythonType*)PyDict_GetItemString(dict,tname.c_str());


    auto pobj = PyObject_New(PythonObject,ptype);

    new (pobj) PythonObject(argument);
    pyObject =pobj;
  }

  if(!pyObject)return false;
  auto dict = PyModule_GetDict(targetModule);
  if(!dict)return false;
  auto result = PyDict_SetItemString(dict,this->name.c_str(),pyObject);
  if(result<0)return false;
  return true;
}

PythonVariable::operator Argument(){
  return toArgument(0);
}
Argument PythonVariable::toArgument(const Type * type){
  PyObject *module = PyImport_AddModule(this->module.c_str());
  if(!module)return Argument();
  auto dict = PyModule_GetDict(module);
  if(!dict)return Argument();
  auto value = PyDict_GetItemString(dict,this->name.c_str());
  if(!dict)return Argument();



  return pythonObjectToArgument(value,type);
}


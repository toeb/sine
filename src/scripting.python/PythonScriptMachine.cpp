#include "PythonScriptMachine.h"
#include <scripting.python/PythonUtilities.h>
#include <scripting.python/PythonMethodAdapter.h>
#include <scripting.python/PythonType.h>
using namespace nspace;


size_t PythonScriptMachine::instances=0;

bool PythonScriptMachine::registerObject(const std::string & variablename, Argument argument){
  if(!registerType(argument.type)){
    return false;
  }
  auto globalModule = PyImport_AddModule("lala");
  auto wrapper = pythonObjectFromArgument(argument);
  auto dict = PyModule_GetDict(globalModule);
  auto result = PyDict_SetItemString(dict,variablename.c_str(),wrapper);

}

PythonScriptMachine::PythonScriptMachine(){
  instances++;
  if(instances==1){
    // todo : python3 does not get the libs correclty
    Py_Initialize();
    initStaticTypes();
  }

}
PythonScriptMachine::~PythonScriptMachine() {
  instances--;
  if(!instances){
    Py_Finalize();
  }
}
void PythonScriptMachine::initStaticTypes(){
  auto mType = PythonMethodType::instance().get();
  if(PyType_Ready(mType)<0){
    logError("could not ready method wrapper")
  }   
  Py_INCREF(mType);
  static PyModuleDef moduleDefinition={
    PyModuleDef_HEAD_INIT,
    "ds.statictypes",
    "module containing static types needed for connecting c library",
    -1,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
  };

  auto module = PyModule_Create(&moduleDefinition);
  if(!module){
    logError("could not init module ds.statictypes");
    return;
  }
  if(PyModule_AddObject(module , "MethodWrapper", (PyObject*)mType)<0){
    logError("could not register MethodWrapper");
    return;
  }
}

namespace nspace{

  struct Module{
    Module(){}
    void addType(const std::string  & name, const Type * type){

    }
    const Namespace * _namespace;
    std::map<std::string,PythonType*> types;
  };
};


PyObject * nspace::pythonObjectFromArgument(Argument arg){
  if(arg.type==typeof(int)){
    return Py_BuildValue("i",(int)arg);
  }

  

  return 0;
}

bool PythonScriptMachine::registerType(const Type * type){
  if(!type){
    logError("cannot register null type");
    return false;
  }
  auto namespaceString = stringtools::replace(type->getNamespace()->getFullyQualifiedName(),"::",".");
  auto module = PyImport_AddModule(stringtools::c_str(namespaceString));

  if(!module){
    logError("could not init module '"<< namespaceString << "'" );
    return false;
  }

  auto pythonType = new PythonType(type);
  types.push_back(pythonType);
  if(PyType_Ready(pythonType)<0){
    logError("could not ready type '"<<type->getName()<<"'");
    return false;
  }

  Py_INCREF(pythonType);



  if(PyModule_AddObject(module,stringtools::c_str(type->getName()),(PyObject*)pythonType)<0){
    logError("could not add type '"<<type->getName()<<"' to module '"<<namespaceString<<"'");
    return false;
  }



  return true;
}

bool PythonScriptMachine::loadStream(std::istream & stream){
  std::istreambuf_iterator<char> eos;
  std::string string(std::istreambuf_iterator<char>(stream), eos);
  return PyRun_SimpleString(string.c_str())==0;
}
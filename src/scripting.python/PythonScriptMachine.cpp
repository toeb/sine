#include "PythonScriptMachine.h"
#include <scripting.python/PythonUtilities.h>
#include <scripting.python/PythonMethodAdapter.h>
#include <scripting.python/PythonType.h>
using namespace nspace;


size_t PythonScriptMachine::instances=0;


PythonScriptMachine::PythonScriptMachine(){
    instances++;
    if(instances==1){
      Py_SetProgramName("PythonScriptMachine");
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
    auto module = Py_InitModule("ds.statictypes",0);
    if(!module){
      logError("could not init module ds.statictypes");
      return;
    }
    if(PyModule_AddObject(module , "MethodWrapper", (PyObject*)mType)<0){
      logError("could not register MethodWrapper");
      return;
    }
  }
  bool PythonScriptMachine::registerType(const Type * type){
    if(!type){
      logError("cannot register null type");
      return false;
    }
    auto namespaceString = stringtools::replace(type->getNamespace()->getFullyQualifiedName(),"::",".");
    auto module = Py_InitModule(namespaceString.c_str(),0);
    if(!module){
      logError("could not init module '"<< namespaceString << "'" );
      return false;
    }

    auto pythonType = new PythonType(type);
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
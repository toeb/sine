#include "PythonScriptMachine.h"
#include <scripting.python/PythonUtilities.h>
#include <scripting.python/PythonMethodAdapter.h>
#include <scripting.python/PythonType.h>
#include <scripting.python/PythonObject.h>
#include <scripting.python/PythonVariable.h>
using namespace nspace;
using namespace std;

size_t PythonScriptMachine::instances=0;


bool parseArguments(PyObject * args,  std::vector<Argument> & arguments, std::vector<ConstTypePtr> & argumentTypes);

bool PythonScriptMachine::setVariable(const std::string & name, Argument argument){
  if(!registerType(argument.type)){
    return false;
  }
  PythonVariable var = name;



  return var.assign( argument);
}


Argument PythonScriptMachine::getVariable(const std::string & name,const Type * type){
  PythonVariable var=name;
  return var.toArgument(type);
}


bool PythonScriptMachine::registerObject(const std::string & variablename, Argument argument){
  return setVariable(variablename,argument);
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
  auto mType = PythonCallableType::instance().get();
  if(PyType_Ready(mType)<0){
    logError("could not ready method wrapper")
  }   

  auto module = PyImport_AddModule("ds.statictypes");
  Py_INCREF(mType);
  
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
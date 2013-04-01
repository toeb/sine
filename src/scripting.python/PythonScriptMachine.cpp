#include "PythonScriptMachine.h"
#include <scripting.python/PythonUtilities.h>
#include <scripting.python/PythonMethodAdapter.h>
#include <scripting.python/PythonType.h>
#include <scripting.python/PythonObject.h>
#include <scripting.python/PythonVariable.h>
using namespace nspace;
using namespace std;

size_t PythonScriptMachine::instances=0;


bool parseArguments(PyObject * args,  std::vector<Argument> & arguments, std::vector<const Type *> & argumentTypes);

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
  auto path = stringtools::wstringToString(Py_GetPath());
  auto paths = stringtools::split(path,';');
  auto first = paths.begin();
  Paths().insert(paths.begin(),paths.end());
  
  // extract installation folder

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

  auto module = PyImport_AddModule("cppinterop");

  
  if(!module){
    logError("could not init module cppinterop");
    return;
  }
  Py_INCREF(mType);
  if(PyModule_AddObject(module , "MethodWrapper", (PyObject*)mType)<0){
    logError("could not register MethodWrapper");
    return;
  }
}



PyObject * requirePythonScope(const ScopeInfo * scope){
  if(!scope||scope==ScopeInfo::Global()){
    return PyImport_AddModule("__main__");
  }


  auto name = formatModuleName(scope);
  /*
  PyModuleDef & moduleDef = *new PyModuleDef();
  PyModuleDef_Base base = PyModuleDef_HEAD_INIT;
  moduleDef.m_base = base;
  moduleDef.m_size = sizeof(const ScopeInfo*);
  moduleDef.m_clear=0;
  moduleDef.m_doc = "C++ Interop Module";
  moduleDef.m_name = stringtools::c_str(name);
  moduleDef.m_traverse=0;
  moduleDef.m_methods=0;
  moduleDef.m_reload=0;
  moduleDef.m_free=0;
  */
  auto module =PyImport_AddModule(stringtools::c_str(name));//parentModule;// PyModule_New(name.c_str());
 // auto dict= PyModule_GetDict(parentModule);
 // PyDict_SetItemString(dict,name.c_str(),module);
  //auto state = (const ScopeInfo**)PyModule_GetState(module);
  //*state = scope;

  if(!module)std::cout << "could create module  '"<<name<<"'"<<std::endl;

  return module;
}
bool PythonScriptMachine::registerType(const Type * type){
  // checks whether a type was already registered and if so returns true
  // else registers the type in python and stores a pointer in types vector

  if(!type){
    logError("cannot register null type");
    return false;
  }

  if(getPythonType(type))return true;

  auto module = requirePythonScope(type->getScope());

  //std::string namespaceString = formatModuleName(type);
  //auto module = PyImport_AddModule(stringtools::c_str(namespaceString));

  if(!module){
    logError("could not init scope for type '" << type->getFullyQualifiedName()<< "'" );
    return false;
  }

  auto pythonType = new PythonType(type);
  
  if(PyType_Ready(pythonType)<0){
    logError("could not ready type '"<<type->getName()<<"'");
    return false;
  }

  types.push_back(pythonType);

  Py_INCREF(pythonType);

  if(PyModule_AddObject(module,type->getName().c_str(),(PyObject*)pythonType)<0){
    logError("could not add type '"<<type->getName()<<"' to module '"<<type->formatScopeName(".")<<"'");
    return false;
  }

  return true;
}

bool PythonScriptMachine::loadStream(std::istream & stream){
  std::istreambuf_iterator<char> eos;
  std::string string(std::istreambuf_iterator<char>(stream), eos);
  return PyRun_SimpleString(string.c_str())==0;
}
#include "PythonFunction.h"
#include <scripting.python/PythonUtilities.h>
using namespace nspace;


PythonFunction::PythonFunction(PyObject * func):func(0){

  if(PyCallable_Check(func)<0)return;
  this->func=func;
  Py_IncRef(func);
}

bool PythonFunction::isValid()const {
  return func!=0;
}
PythonFunction::~PythonFunction(){
  Py_DecRef(func);
}
Argument PythonFunction::call(std::vector<Argument> & args){
  if(!isValid())return Argument();
  auto tuple = PyTuple_New(args.size());
  for(int i=0; i < args.size();i++){
    auto obj  =pythonObjectFromArgument(args[i]);
    PyTuple_SetItem(tuple,i,obj);
  }
  auto pythonResult =PyObject_Call(func,tuple,NULL);
  Argument result= pythonObjectToArgument(pythonResult,0);
  Py_DecRef(pythonResult);
  return result;
}
#include "PythonMethodAdapter.h"
#include <scripting.python/PythonUtilities.h>
#include <core.reflection.h>
#include <vector>
using namespace nspace;

struct PythonMethodAdapter:PyObject,MethodAdapter{
};

bool parseArguments(PyObject * args,  std::vector<Argument> & arguments, std::vector<ConstTypePtr> & argumentTypes){  
  PyTuple_Check(args);
  auto n=PyTuple_GET_SIZE(args);

  if(n!=argumentTypes.size()){
    false;
  }


  for(int i=0; i < n; i++){
    auto argType = argumentTypes[i];
    auto argPythonObject = PyTuple_GET_ITEM(args,i);
    auto argument = pythonObjectToArgument(argPythonObject,argType);
    if(!argument.isValid()){
      arguments.clear();
      return false;
    }
    arguments.push_back(argument);      
  }
  return true;
}
static PyObject * call(PyObject * object, PyObject* args, PyObject* kwds){
  auto methodAdapter = static_cast<PythonMethodAdapter*>(object);
  auto methodInfo = methodAdapter->getMethodInfo();
  auto methodArgTypes = methodInfo->getArgumentTypes();

  // parse arguments from tuple
  std::vector<Argument> arguments;
  parseArguments(args,arguments,methodArgTypes);
  auto result = methodAdapter->call(arguments);
  auto pythonResult = pythonObjectFromArgument(result);
  return pythonResult;
}
PyObject * construct(PyTypeObject *subtype, PyObject *args, PyObject *kwds){return 0;}
void destruct(void * object){}
PythonMethodType::PythonMethodType(){
  PyTypeObject tmp={PyObject_HEAD_INIT(NULL)};
  ((PyTypeObject&)*this)=tmp;
  tp_name="MethodWrapper";
  tp_call=&call;

  tp_basicsize=sizeof(PythonMethodType);
  tp_itemsize=0;


  // memroy allocation and deallocation
  tp_alloc = PyType_GenericAlloc; 
  tp_dealloc = 0;

  //constructor
  tp_new=PyType_GenericNew;
  tp_free =&destruct;


}
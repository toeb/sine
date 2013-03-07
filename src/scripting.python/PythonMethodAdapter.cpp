#include "PythonMethodAdapter.h"
#include <scripting.python/PythonUtilities.h>
#include <core.reflection.h>
#include <vector>
using namespace nspace;

struct PythonMethodAdapter:PyObject,MethodAdapter{
};

bool parseArguments(PyObject * args,  std::vector<Argument> & arguments, std::vector<ConstTypePtr> * argumentTypes){  
  PyTuple_Check(args);
  auto n=PyTuple_GET_SIZE(args);
  if(!argumentTypes){
    // only infer arguments if types not passed
    for(int i=0; i < n;i++){
      auto arg = pythonObjectToArgument(PyTuple_GetItem(args,i),0);
      arguments.push_back(arg);
    }
    return true;
  }
  // else use passed types to construct argument
  if(n!=argumentTypes->size())return false;
  for(size_t i=0; i < argumentTypes->size(); i++){
    auto argType = argumentTypes->at(i);
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
  auto callable = static_cast<PythonCallable*>(object);

  std::vector<Argument> cargs;
  auto success=  parseArguments(args,cargs,0);
  if(!success)return 0;
  auto result = callable->callable(cargs);
  return pythonObjectFromArgument(result);
}
PyObject * construct(PyTypeObject *subtype, PyObject *args, PyObject *kwds){return 0;}
void destruct(void * object){}
PythonCallableType::PythonCallableType(){
  PyTypeObject tmp={PyObject_HEAD_INIT(NULL)};
  ((PyTypeObject&)*this)=tmp;
  tp_name="MethodWrapper";
  tp_call=&call;

  tp_basicsize=sizeof(PythonCallableType);
  tp_itemsize=0;


  // memroy allocation and deallocation
  tp_alloc = PyType_GenericAlloc; 
  tp_dealloc = 0;

  //constructor
  tp_new=PyType_GenericNew;
  tp_free =&destruct;


}
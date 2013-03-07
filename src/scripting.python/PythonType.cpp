#include "PythonType.h"
#include <core.utility/StringTools.h>
#include <scripting.python/PythonObject.h>
using namespace nspace;
using namespace std;

PyObject * constructCallback(PyTypeObject* subtype, PyObject*args, PyObject * kwds){
  auto  pythonType = static_cast<PythonType*>(subtype);
  return pythonType->construct(args,kwds);
  
}

  bool parseArguments(PyObject * args,  std::vector<Argument> & arguments, std::vector<ConstTypePtr> & argumentTypes);

PyObject * PythonType::construct( PyObject *args, PyObject *kwds){
  const ConstructorInfo * constructor = 0;
  std::vector<Argument> arguments;
  for(int i=0; i < type->Constructors().size(); i++){
    auto currentConstructor = type->Constructors().at(i);
    auto argumentTypes = currentConstructor->getArgumentTypes();
    if(parseArguments(args,arguments,argumentTypes)){
      constructor = currentConstructor;
      break;
    }
  }
  if(!constructor){
    std::cerr << "could not find matching constructor"<<std::endl;
    return 0;
  }
  auto result = constructor->call();
  
  return new PythonObject(result);

}
void       PythonType::destruct(void * object){ }
PyObject * PythonType::getProperty(PyObject* pobject, PyObject * name ){return 0; }
int        PythonType::setProperty(PyObject * object, PyObject * , PyObject* value){return 0;}
PyObject *PythonType:: stringRepresentation(PyObject * object){return 0; }
PythonType::PythonType(const Type* type):type(type){
  auto ns = type->getNamespace();
  string namespaceString= stringtools::replace(ns->getFullyQualifiedName(),"::",".")+"."+type->getName();
  string docString = "wrapper for "+namespaceString;

  //initialize head
  PyTypeObject tmp={PyObject_HEAD_INIT(NULL)};
  ((PyTypeObject&)*this)=tmp;

  tp_name = stringtools::c_str(namespaceString);
  tp_basicsize = sizeof(PythonObject);
  tp_repr = &stringRepresentation;
  tp_getattro=&getProperty;
  tp_setattro=&setProperty;
  tp_doc = stringtools::c_str(docString);

  //initialization function (may be called multiple times)
  tp_init=0;  
  // memroy allocation and deallocation
  tp_alloc = PyType_GenericAlloc; 
  tp_dealloc = 0;

  //constructor
  tp_new= &constructCallback;
  tp_free =&destruct;
  //  indicates wheter instance can be collected
  tp_is_gc=0;
  // tuple of base types
  tp_bases =0;
  // Tuple containing the expanded set of base types, starting with the type itself and ending with object, in Method Resolution Order.
  tp_mro=0;    
}
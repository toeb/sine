#include <core.testing.h>


// if debug is defined then some more unlinkable functions will be added
// so i disable the debug flag for python.h
#ifdef _DEBUG
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif

#include <core.utility/StringTools.h>
using namespace std;
using namespace nspace;


#define reflected_method(NAME) DS_CONCAT(NAME,ReturnType); reflect_method(NAME); public: DS_CONCAT(NAME,ReturnType) NAME
struct TestType{
  reflect_type(TestType);

  reflected_default_constructor(public: TestType){};

  typedef void reflected_method(method1)(){}
 typedef int reflected_method(method2)(){return 3;}
  typedef int reflected_method(increment)(int i){return i;}
  typedef int reflected_method(add)(int a, int b){return a+b;}

}a;

struct PythonProperty{
  PyObject_HEAD;
  PythonProperty(PropertyAdapter property):property(property){}
  PropertyAdapter property;
};
struct PythonMethod{
  PyObject_HEAD;
  PythonMethod(MethodAdapter method):method(method){}
  MethodAdapter method;
};
struct PythonObject{
  PyObject_HEAD;
  PythonObject(Argument object):object(object){
    auto m = object.type->Methods().elements();
    auto p = object.type->Properties().elements();
    for(auto method : m){
      MethodAdapter adapter(object,method);
      methods.push_back(PythonMethod(adapter));
    }
    for(auto property : p){
      PropertyAdapter adapter(object,property);
      properties.push_back(PythonProperty(adapter));
    }
  }
  Argument object;
  std::vector<PythonProperty> properties;
  std::vector<PythonMethod> methods;
};

struct PythonType : public PyTypeObject{
  PythonType(const Type* type):type(type){
  }
  const Type * type;
};
struct PythonMethodInfo : public PyMethodDef{
  PythonMethodInfo(){

  }
};


PyObject *construct(PyTypeObject *subtype, PyObject *args, PyObject *kwds){
  //The tp_new function should call subtype->tp_alloc(subtype, nitems) to allocate space for the object,
  // and then do only as much further initialization as is absolutely necessary. 
  // Initialization that can safely be ignored or repeated should be placed in the tp_init handler. 
  // A good rule of thumb is that for immutable types, all initialization should take place in tp_new,
  //  while for mutable types, most initialization should be deferred to tp_init.
  auto pType = static_cast<PythonType*>(subtype);
  auto rType = pType->type;
  auto constructor = rType->Constructors().first([](const ConstructorInfo * c){return c->getArgumentTypes().size()==0;});
  if(!constructor){
    return 0;
  }
  auto instance = constructor->call();
  // allocate memory
  PythonObject * result = (PythonObject*)subtype->tp_alloc(subtype, 0);
  if(result==0){
    return 0;
  }
  // call constructor on memory area
  new (result) PythonObject(instance);
  
  return (PyObject*)result;
}
void destruct(void * object){

}
int print(PyObject * object, FILE* , int){return 0;}
PyObject * get_property(PyObject* object, PyObject * ){
  return PyString_FromString("helllo you");
}
int set_property(PyObject * object, PyObject * , PyObject* value){return 0;}
PyObject * stringRepresentation(PyObject * object){return 0;}
PyObject * call_method(PyObject * self, PyObject * args){return 0;}
PyObject * call(PyObject * ,PyObject * ,PyObject * ){return 0;};
char * copyCStr(const std::string  & text){
  char *cDocString = new char[text.size()+1]; // +1 to account for \0 byte
  std::strncpy(cDocString, text.c_str(), text.size());
  cDocString[text.size()]=0;// ensure it is null terminated ( if it is not already)
  return cDocString;
}


PyTypeObject * createPythonType(const Type * reflectType){
  auto ns = reflectType->getNamespace();
  string namespaceString= stringtools::replace(ns->getFullyQualifiedName(),"::",".")+"."+reflectType->getName();
  string docString = "wrapper for "+namespaceString;

  PyTypeObject & pythonType=*new PythonType(reflectType);
  //initialize head
  PyTypeObject tmp={PyObject_HEAD_INIT(NULL)};
  pythonType = tmp;
  

  pythonType.ob_refcnt=0;
  pythonType.ob_size=0;

  pythonType.tp_name = copyCStr(namespaceString);
  pythonType.tp_basicsize = sizeof(PythonObject);
  pythonType.tp_itemsize = 0;
  // standard ops
  pythonType.tp_print= &print;
  pythonType.tp_getattr = 0;// deprecated --> tp_getattro
  pythonType.tp_setattr = 0; //  "        -->   "s"
  pythonType.tp_compare=0;
  pythonType.tp_repr = &stringRepresentation;

  // method suites for standard classes
  pythonType.tp_as_number=0;
  pythonType.tp_as_sequence=0;
  pythonType.tp_as_mapping=0;

  // standard ops for binary compatablility
  pythonType.tp_hash=0;
  pythonType.tp_call=call;
  pythonType.tp_str=0;
  pythonType.tp_getattro=&get_property;
  pythonType.tp_setattro=&set_property;

  pythonType.tp_as_buffer = 0;
  pythonType.tp_flags=0;
  pythonType.tp_doc = copyCStr(docString);
  // only when tpflags_have_rechcompare is set
  pythonType.tp_traverse =0;
  pythonType.tp_clear=0;
  pythonType.tp_richcompare=0;

  pythonType.tp_weaklistoffset=0;
  pythonType.tp_iter=0;
  pythonType.tp_iternext=0;


  // fields for mapping c members
  pythonType.tp_methods=0;
  pythonType.tp_members=0; 
  pythonType.tp_getset=0;


  pythonType.tp_base=0;
  pythonType.tp_dict=0;
  pythonType.tp_descr_get=0;
  pythonType.tp_descr_set=0;
  pythonType.tp_dictoffset=0;

  //initialization function (may be called multiple times)
  pythonType.tp_init=0;  
  // memroy allocation and deallocation
  pythonType.tp_alloc = PyType_GenericAlloc; 
  pythonType.tp_dealloc = 0;

 //constructor
  pythonType.tp_new= &construct;
  pythonType.tp_free =&destruct;
  //  indicates wheter instance can be collected
  pythonType.tp_is_gc=0;
  // tuple of base types
  pythonType.tp_bases =0;
  // Tuple containing the expanded set of base types, starting with the type itself and ending with object, in Method Resolution Order.
  pythonType.tp_mro=0;  

    
  return &pythonType;
};

void init(){
  
  auto m= Py_InitModule("ds",0);
  auto pType = createPythonType(typeof(TestType));
  if(PyType_Ready(pType)<0){
    
  }
  //PyModule_AddStringConstant(m, "__file__","ds.ply");
  Py_INCREF(pType);
  if(PyModule_AddObject(m, "TestType", (PyObject*)pType)<0){
    std::cout <<"meh";
  }
}
TEST(2,Python){
  
  PyImport_AppendInittab("ds",&init);
  Py_SetProgramName("Python Test 2");  
  Py_Initialize();
  
  PyRun_SimpleString(
    "import ds\n"
    "print ds.TestType\n"
    "hihi = ds.TestType()\n"
    "print hihi\n"
    );

  Py_Finalize();
}


TEST(1,Python){
 
    // Initialize the Python Interpreter
    Py_Initialize();
    
    // Build the name object
    auto pName = PyString_FromString("py_function");

    // Load the module object
    auto pModule = PyImport_Import(pName);

    // pDict is a borrowed reference 
    auto pDict = PyModule_GetDict(pModule);

    // pFunc is also a borrowed reference 
   auto pFunc = PyDict_GetItemString(pDict, "multiply");

    if (PyCallable_Check(pFunc)) 
    {
        PyObject_CallObject(pFunc, NULL);
    } else 
    {
        PyErr_Print();
    }

    // Clean up
    Py_DECREF(pModule);
    Py_DECREF(pName);

    // Finish the Python Interpreter
    Py_Finalize();


}


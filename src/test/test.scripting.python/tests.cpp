#include <core.testing.h>
#include <scripting.python.h>

#include <map>
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

char * copyCStr(const std::string  & text){
  char *cDocString = new char[text.size()+1]; // +1 to account for \0 byte
  std::strncpy(cDocString, text.c_str(), text.size());
  cDocString[text.size()]=0;// ensure it is null terminated ( if it is not already)
  return cDocString;
}


#define reflected_method(NAME) DS_CONCAT(NAME,ReturnType); reflect_method(NAME); public: DS_CONCAT(NAME,ReturnType) NAME
struct TestType{
  reflect_type(TestType);

  reflected_default_constructor(public: TestType){};

  typedef void reflected_method(method1)(){}
  typedef int  reflected_method(method2)(){return 3;}
  typedef int  reflected_method(increment)(int i){return i+1;}
  typedef int  reflected_method(add)(int a, int b){return a+b;}

}a;

struct PythonObject:public PyObject{
  PythonObject(Argument object):object(object){}
  //converts a PyObject to a PythonObject (int or
  PythonObject(PyObject * pObject){

  }
  // converts PythonObject to a pyObject * 
  operator PyObject * (){

  }

  Argument object;
  std::map<std::string, PyObject*> members;



};
struct PythonPropertyAdapter:public PyObject, public PropertyAdapter{
  PythonPropertyAdapter(Argument object,const PropertyInfo* info):PropertyAdapter(object,info){}
};



struct PythonMethodAdapter:public PyObject, public MethodAdapter{  
  PythonMethodAdapter(Argument object,const MethodInfo* info):MethodAdapter(object,info){}
};


struct PythonType : public PyTypeObject{

  static PyObject * construct(PyTypeObject *subtype, PyObject *args, PyObject *kwds){return 0; }
  static void       destruct(void * object){ }
  static PyObject * getProperty(PyObject* pobject, PyObject * name ){return 0; }
  static int        setProperty(PyObject * object, PyObject * , PyObject* value){return 0;}
  static PyObject * stringRepresentation(PyObject * object){return 0; }

  PythonType(const Type* type):type(type){
    auto ns = type->getNamespace();
    string namespaceString= stringtools::replace(ns->getFullyQualifiedName(),"::",".")+"."+type->getName();
    string docString = "wrapper for "+namespaceString;

    //initialize head
    PyTypeObject tmp={PyObject_HEAD_INIT(NULL)};
    ((PyTypeObject&)*this)=tmp;

    tp_name = copyCStr(namespaceString);
    tp_basicsize = sizeof(PythonObject);
    tp_repr = &stringRepresentation;
    tp_getattro=&getProperty;
    tp_setattro=&setProperty;
    tp_doc = copyCStr(docString);

    //initialization function (may be called multiple times)
    tp_init=0;  
    // memroy allocation and deallocation
    tp_alloc = PyType_GenericAlloc; 
    tp_dealloc = 0;

    //constructor
    tp_new= &construct;
    tp_free =&destruct;
    //  indicates wheter instance can be collected
    tp_is_gc=0;
    // tuple of base types
    tp_bases =0;
    // Tuple containing the expanded set of base types, starting with the type itself and ending with object, in Method Resolution Order.
    tp_mro=0;    
  }
  const Type * type;
};

Argument pythonObjectToArgument(PyObject * object, const Type * type){

  if(PyNumber_Check(object)){
    if(type->getName()=="int"){
      auto pyInt = PyNumber_Int(object);
      auto integer = (int)PyInt_AsLong(pyInt);
      return integer;
    }
  }
  /*
  auto pyType = (PyTypeObject*)PyObject_Type(object);  
  if(!pyType)return Argument();
  */


  return Argument();
}
PyObject * pythonObjectFromArgument(Argument argument){
  if(argument.type->getName()=="int"){
    int value = argument;
    return Py_BuildValue("i",value);
  }

  return 0;
}

struct PythonMethodType:PyTypeObject{
  static PyObject* call(PyObject * object, PyObject* args, PyObject* kwds){
    auto methodAdapter = static_cast<PythonMethodAdapter*>(object);
    auto methodInfo = methodAdapter->getMethodInfo();
    auto methodArgs = methodInfo->getArgumentTypes();
    // parse arguments from tuple

    PyTuple_Check(args);
    auto n=PyTuple_GET_SIZE(args);

    if(n!=methodArgs.size()){

      return 0;
    }

    std::vector<Argument> arguments;

    for(int i=0; i < n; i++){
      auto argType = methodArgs[i];
      auto argPythonObject = PyTuple_GET_ITEM(args,i);
      auto argument = pythonObjectToArgument(argPythonObject,argType);
      arguments.push_back(argument);      
    }
    auto result = methodAdapter->call(arguments);
    auto pythonResult = pythonObjectFromArgument(result);
    return pythonResult;
  }
  static PyObject * construct(PyTypeObject *subtype, PyObject *args, PyObject *kwds){return 0;}
  static void destruct(void * object){}
  PythonMethodType(){
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
}static pythonMethodType;

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

PyObject * get_property(PyObject* pobject, PyObject * name ){
  auto object =static_cast<PythonObject*>(pobject);
  auto propertyName = PyString_AsString(name);
  if(object->members.find(propertyName)==end(object->members)){
    auto reflectMethod = object->object.type->getMethod(propertyName);
    if(reflectMethod){      
      auto adapter = PyObject_New(PythonMethodAdapter,&pythonMethodType);
      // construct cpp object over python object
      new (adapter) PythonMethodAdapter(object->object,reflectMethod);
      // store member in objects member table
      object->members[propertyName]=adapter;
      return adapter;
    }
    auto reflectProperty = object->object.type->getProperty(propertyName);
    if(reflectProperty){

    }
    // return default: null value
    return Py_BuildValue("");

  }
  auto member = object->members.at(propertyName);


  return PyString_FromString("helllo you");
}
int set_property(PyObject * object, PyObject * , PyObject* value){return 0;}
PyObject * stringRepresentation(PyObject * object){
  auto obj = static_cast<PythonObject*>(object);
  auto name = obj->object.type->getName();

  return PyString_FromString(name.c_str());

}
PyObject * call_method(PyObject * self, PyObject * args){return 0;}
PyObject * call(PyObject * ,PyObject * ,PyObject * ){return 0;};

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
  pythonType.tp_print= 0;
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
  if(PyType_Ready(pType)<0){ }
  auto mType = &pythonMethodType;
  if(PyType_Ready(mType)<0){
    std::cout << "could not ready method wrapper"<<std::endl;

  }

  Py_INCREF(pType);

  if(PyModule_AddObject(m, "TestType", (PyObject*)pType)<0){
    std::cout <<"meh";
  }
  Py_INCREF(mType);
  if(PyModule_AddObject(m, "MethodWrapper", (PyObject*)mType)<0){
    std::cout << "could not register method wrapper"<<std::endl;
  }
}
/*
TEST(2,Python){


PyImport_AppendInittab("ds",&init);

Py_SetProgramName("Python Test 2");  
Py_Initialize();

PyRun_SimpleString(
"import ds\n"
"print ds.TestType\n"
"print ds.MethodWrapper\n"
"hihi = ds.TestType()\n"
"print hihi.increment(3)\n"
);

Py_Finalize();
}*/

class PythonScriptMachine : public VirtualScriptMachine{
  static size_t instances;
public:
  PythonScriptMachine(){
    instances++;
    if(instances==1){
      Py_SetProgramName("PythonScriptMachine");
      Py_Initialize();
      initStaticTypes();
    }

  }
  ~PythonScriptMachine() override{
    instances--;
    if(!instances){
      Py_Finalize();
    }
  }
  void initStaticTypes(){
    auto mType = &pythonMethodType;
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
  bool registerType(const Type * type){
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

    if(PyModule_AddObject(module,copyCStr(type->getName()),(PyObject*)pythonType)<0){
      logError("could not add type '"<<type->getName()<<"' to module '"<<namespaceString<<"'");
      return false;
    }

    return true;
  }

  bool loadStream(std::istream & stream){
    std::istreambuf_iterator<char> eos;
    std::string string(std::istreambuf_iterator<char>(stream), eos);
    return PyRun_SimpleString(string.c_str())==0;
  }
};

size_t PythonScriptMachine::instances=0;



TEST(Instanciate,RegisterType){
  PythonScriptMachine machine;
  machine.registerType(typeof(TestType));
  auto success = machine.loadString(
    "import ds\n"
    "import ds.TestType\n"
    "import inspect\n"
    "print ds.TestType\n"
    "t = ds.TestType\n"
    "for symbol, value in locals().items():\n"
    "\tprint symbol, value\n"
    "b = new TestType()\n"
  );
  CHECK(success);
}

TEST(CheckExists, RegisterType){
  PythonScriptMachine machine;
  CHECK(machine.registerType(typeof(TestType)));
  auto result = PyRun_SimpleString(
    "import ds\n"
    "print ds.TestType"
    );
  CHECK(result==0);
}
TEST(4,PythonInitialization){
  PythonScriptMachine machine;
  PyRun_SimpleString(
    "import ds.statictypes\n"
    "print MethodWrapper\n"
    );
}
TEST(3,PythonInitialization){
  CHECK(!Py_IsInitialized());
  {
    PythonScriptMachine machine;    
    PythonScriptMachine machine2;
    CHECK(Py_IsInitialized());
  }
  CHECK(!Py_IsInitialized());
}
TEST(2,PythonInitialization){
  CHECK(!Py_IsInitialized());
  {
    PythonScriptMachine machine;    
    CHECK(Py_IsInitialized());
  }
  CHECK(!Py_IsInitialized());
}

TEST(1,PythonInitialization){
  PythonScriptMachine machine;
  CHECK(Py_IsInitialized());  
}



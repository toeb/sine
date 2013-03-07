#include <core.testing.h>
#include <scripting.python/PythonUtilities.h>
#include <scripting.python.h>
#include <map>


#include <core.utility/StringTools.h>
using namespace std;
using namespace nspace;


#define reflected_method(NAME) DS_CONCAT(NAME,ReturnType); reflect_method(NAME); public: DS_CONCAT(NAME,ReturnType) NAME
struct TestType{
  int initialValue;
  reflect_type(TestType);
  reflected_default_constructor(public: TestType):initialValue(0){};
  reflected_constructor(public: TestType, int a):initialValue(a){};
  typedef void reflected_method(method1)(){}
  typedef int  reflected_method(method2)(){return 3;}  
  typedef int  reflected_method(increment)(int i){return i+1;}
  typedef int  reflected_method(add)(int a, int b){return a+b;}
  

}a;


TEST(1,AddObject){
  PythonScriptMachine machine;
  TestType t;
  auto result = machine.registerObject("testvar",23);
  CHECK(result);
   result = machine.loadString(
    "import ds\n"
    "import lala\n"
    "print(testvar)\n"
    );
   CHECK(result);

}

TEST(1,AddObject){
  PythonScriptMachine machine;
  
  auto result = machine.registerObject("testvar",23);
  CHECK(result);
   result = machine.loadString(
    "import ds\n"
    "import lala\n"
    "print(testvar)\n"
    );
   CHECK(result);
}


TEST(CheckExists, RegisterType){
  PythonScriptMachine machine;
  CHECK(machine.registerType(typeof(TestType)));
  auto result = PyRun_SimpleString(
    "import ds\n"
    "print (ds.TestType)\n"
    );
  CHECK(result==0);
}
TEST(StringRepresentation,RegisterType){
  PythonScriptMachine machine;
  machine.registerType(typeof(TestType));
  auto success = machine.loadString(
    "import ds\n"
    "print(ds.TestType())"// somehow get text output to compare

  );

  CHECK(success);
}

TEST(Instanciate2, RegisterType){
   PythonScriptMachine machine;
  machine.registerType(typeof(TestType));
  auto success = machine.loadString(
    "import ds\n"
    "ds.TestType(3)"
  );
  CHECK(success);
}

TEST(Instanciate1,RegisterType){
  PythonScriptMachine machine;
  machine.registerType(typeof(TestType));
  auto success = machine.loadString(
    "import ds\n"
    "ds.TestType()"
  );
  CHECK(success);
}

TEST(4,PythonInitialization){
  PythonScriptMachine machine;
  PyRun_SimpleString(
    "import ds.statictypes\n"
    "print(MethodWrapper)\n"
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



#include <core.testing.h>
#include <scripting.python/PythonUtilities.h>
#include <scripting.python.h>
#include <map>


#include <core.utility/StringTools.h>
using namespace std;
using namespace nspace;


#define reflected_method(NAME) DS_CONCAT(NAME,ReturnType); reflect_method(NAME); public: DS_CONCAT(NAME,ReturnType) NAME
struct TestType{
  reflect_type(TestType);

  reflected_default_constructor(public: TestType){};

  typedef void reflected_method(method1)(){}
  typedef int  reflected_method(method2)(){return 3;}
  typedef int  reflected_method(increment)(int i){return i+1;}
  typedef int  reflected_method(add)(int a, int b){return a+b;}

}a;





TEST(Instanciate,RegisterType){
  PythonScriptMachine machine;
  machine.registerType(typeof(TestType));
  auto success = machine.loadString(
    "import ds\n"
    "ds.TestType()"
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



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



TEST(1,GetVariable){
  PythonScriptMachine machine;
  // needed so that 'import lala' works
  PyImport_AddModule("lala");
  machine.loadString(
    "import lala\n"
    "lala.testVar = 42\n"
    );
  auto var = machine.getVariable("lala.testVar",typeof(int));
  CHECK_EQUAL(42,(int)var);
}
TEST(2,GetVariable){
  PythonScriptMachine machine;
  machine.loadString(
    "aValue= 141\n"
    );
  auto var = machine.getVariable("aValue",typeof(int));
  CHECK_EQUAL(141,(int)var);
}
TEST(3,GetVariable){
  PythonScriptMachine machine;
  auto var = machine.getVariable("nonexistantvariable",typeof(int));
  CHECK(!var.isValid());
}
TEST(4,GetVariable){
  PythonScriptMachine machine;
  machine.loadString(
    "aValue=42\n"
    );
  auto var = machine.getVariable<int>("aValue");
  CHECK_EQUAL(42,var);
}
TEST(String1,GetVariable){
  PythonScriptMachine machine;
  machine.loadString(
    "sValue='hello, hello - turn the radio on'\n"
    );
  auto var = machine.getVariable<std::string>("sValue");
  CHECK_EQUAL("hello, hello - turn the radio on",var);
}
TEST(1,SetVariable){
  // just test wether code referenceing a var of complex type executes correctly
  PythonScriptMachine machine;
  TestType t;
  auto result = machine.setVariable("testvar",t);
  CHECK(result);
  result = machine.loadString(
    "print(testvar)\n"
    );
  CHECK(result);

}
TEST(2,SetVariable){
  // test if data pointer stays the same
  PythonScriptMachine machine;
  std::shared_ptr<TestType> expected(new TestType(32));  
  auto result = machine.setVariable("testvar",expected);  
  auto var= machine.getVariable("testvar");
  std::shared_ptr<TestType> actual = var;
  CHECK_EQUAL(expected.get(),actual.get());
}



TEST(2,AddObject){
  PythonScriptMachine machine;

  auto result = machine.registerObject("testvar",23);
  CHECK(result);
  result = machine.loadString(
    "print(testvar)\n"
    );
  CHECK(result);
  
  machine.getVariable("testvar",typeof(int));
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



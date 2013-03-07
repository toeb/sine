#include <core.testing.h>
#include <scripting.python/PythonUtilities.h>
#include <scripting.python.h>
#include <map>
#include <core.reflection/callable/DelegateAction.h>

#include <core.utility/StringTools.h>
using namespace std;
using namespace nspace;


#define reflected_method(NAME) DS_CONCAT(NAME,ReturnType); reflect_method(NAME); public: DS_CONCAT(NAME,ReturnType) NAME
struct TestType{
  int initialValue;
  reflect_type(TestType);
  reflected_default_constructor(public: TestType):initialValue(0){};
  reflected_constructor(public: TestType, int a):initialValue(a){
  
  };
  typedef void reflected_method(method1)(){}
  typedef int  reflected_method(method2)(){return 3;}  
  typedef int  reflected_method(increment)(int i){return i+1;}
  typedef int  reflected_method(add)(int a, int b){
    return a+b;
  }

  typedef int reflected_method(AddInitialValues)(const TestType & t){
    return initialValue+t.initialValue;
  }
}a;

UNITTEST(CallCLambda3){
  // does the same as CallCLambda2 with auto conversion
  PythonScriptMachine machine;
  machine.setFunctor("herroWolrd",[](std::string s)->std::string{return "herror";} );
  machine.loadString("a = herroWolrd('nihau')");
  auto a = machine.getVariable("a");
  CHECK_EQUAL("herror",(std::string)a);
}
UNITTEST(CallCLambda2){
  // does the same as CallCLambda1 without requiering a reference . a rvalue suffices
  PythonScriptMachine machine;
  machine.setFunction("herroWolrd",make_callable([](std::string s)->std::string{return "herror";}) );
  machine.loadString("a = herroWolrd('nihau')");
  auto a = machine.getVariable("a");
  CHECK_EQUAL("herror",(std::string)a);
}
UNITTEST(CallCLambda1){
  PythonScriptMachine machine;
  auto c=make_callable([](std::string s)->std::string{return "herror";});
  machine.setFunction("herroWolrd",c );
  machine.loadString("a = herroWolrd('nihau')");
  auto a = machine.getVariable("a");
  CHECK_EQUAL("herror",(std::string)a);
}


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
TEST(Lambda1,Call){
  PythonScriptMachine machine;
  machine.loadString(
    "fuu = lambda :  'herro'\n"
    );
  auto func = machine.getVariable<ScriptFunction>("fuu");
  auto result = func();
  CHECK_EQUAL("herro", (std::string)result);
}
TEST(Function1,Call){
  PythonScriptMachine machine;
  machine.loadString("def fuu2():return 'herro'\n");
  auto func = machine.getVariable<ScriptFunction>("fuu2");
  auto result = func();
  auto r = (std::string)result;
  CHECK(result.isValid());
  CHECK_EQUAL("herro",(std::string)result);
}
TEST(Function2,Call){
  PythonScriptMachine machine;
  auto res =  machine.loadString("def fuu3(intval): print(\"meh\"+str(intval)); return 'meh'+str(intval)\nfuu3(32)\n");

  auto func = machine.getVariable<ScriptFunction>("fuu3");
  auto result = func(42);
  CHECK(result.isValid());
  CHECK_EQUAL("meh42",(std::string)result);
}


TEST(CallableAction,Call){
  PythonScriptMachine machine;
  bool called = false;
  
  DelegateAction<std::function<void()>> action([&](){
    called = true;
  });

  machine.setFunction("fuu4",action);
  CHECK(!called);
  machine.loadString(
    "fuu4()\n"
    );
  CHECK(called);
}


TEST(BinaryMethodAdapter,Call){
  PythonScriptMachine machine;
  TestType t;
  MethodAdapter adapter(t,"add");
  machine.setFunction("aNiceMethod",&adapter);
  machine.loadString(
    "a = aNiceMethod(21,84)\n"
    );
  auto result = (int)machine.getVariable("a");
  CHECK_EQUAL(105,result);
}
TEST(ComplexMethod,Call){
  FAIL("Not implemented");
  return;
  PythonScriptMachine machine;
  TestType b(3232);
  machine.setVariable("b",b);
  machine.registerType(typeof(TestType));
  machine.loadString(
    "import ds;\n"
    "a = ds.TestType(2323)\n"
    "c=a.add(3,3)\n"
    );
  auto result = (int)machine.getVariable("c");
  CHECK_EQUAL(5555,result);  
    
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
TEST(String1,SetVariable){
  // tests if string is correctly set
  PythonScriptMachine machine;
  machine.setVariable("sValue",std::string("some string value"));
  machine.loadString("print(sValue)\n");
  auto str = machine.getVariable<std::string>("sValue");
  CHECK_EQUAL("some string value", str);
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



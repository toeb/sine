#include <core.testing.h>
#include <core.reflection.h>


using namespace nspace;
/*
// ////////           --------------------------------------------------------------  external reflect
namespace TestNameSpace{
  
  struct TestType2{
    static int instanceCount;
    bool method1Called;
    TestType2():method1Called(false){instanceCount++;}  
    ~TestType2(){instanceCount--;}  
    int method1(int i){method1Called=true; return i+1;}
    typedef std::string basic_property(Prop1);
  };
  int TestType2::instanceCount = 0;
}


reflect_begin(TestNameSpace::TestType2)
  _method(method1)
  _property(Prop1,getProp1,setProp1)
  _default_constructor(TestType)
  reflect_end

  UNITTEST(ExternalReflection1){

    CHECK_EQUAL(0,TestNameSpace::TestType2::instanceCount);
    auto t = typeof(TestNameSpace::TestType2);
    auto & constructor = *t->Constructors().first();
    auto instance = constructor();
    auto typedInstace = instance.cast<TestNameSpace::TestType2>();
    MethodAdapter mAdapter(instance,"method1");
    int result = mAdapter(3);
    CHECK_EQUAL(4,result);
    PropertyAdapter prop(instance,"Prop1");
    prop.set(std::string("meh"));
    std::string val = prop.get();
    CHECK_EQUAL("meh",val);
}

// ////////           --------------------------------------------------------------  end external reflect

*/
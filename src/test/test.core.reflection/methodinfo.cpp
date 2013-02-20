#include <core.testing.h>

using namespace nspace;
using namespace std;

UNITTEST(MethodInfoMetaDataConst){
  setTestDescription("Tests whether the const flag is properly set for Method info");
  struct A{
    DS_CLASS(A);
    DS_REFLECTION_METHOD(a);
    DS_REFLECTION_METHOD(b);
    DS_REFLECTION_METHOD(c);
    DS_REFLECTION_METHOD(d);
    DS_REFLECTION_METHOD(e);
    DS_REFLECTION_METHOD(f);
    void a()const{}
    void b(){}
    void c(int)const{}
    void d(int){}
    int e()const{return 0;}
    int f(){return 0;}
  }instance;// one instance is needed else reflection will not be initialized for the class
  // get type
  auto type =type_of(instance);
  auto a = type->getMethodInfo("a");
  auto b = type->getMethodInfo("b");
  auto c = type->getMethodInfo("c");
  auto d = type->getMethodInfo("d");
  auto e = type->getMethodInfo("e");
  auto f = type->getMethodInfo("f");
  
  CHECK(a->getIsConst());
  CHECK(!b->getIsConst());
  CHECK(c->getIsConst());
  CHECK(!d->getIsConst());
  CHECK(e->getIsConst());
  CHECK(!f->getIsConst());

}


UNITTEST(virtualMethodReflection1){
  struct A{
    virtual void testMethod1();
  };
}



UNITTEST(ReflectConstMethodThreeArgumentsNonVoidReturnType){
  struct TestStruct{
    DS_CLASS(TestStruct);
    DS_REFLECTION_METHOD(testMethod);
    virtual int testMethod(int i, int j, int k)const{
      cout << i<<j<<k<<endl;
      return i+j+k;
    };
  }t;

  auto type = type_of(t);
  auto member = (const MethodInfo*)type->Members().first();

  int args[3]={3,4,5};

  auto result = member->call(&t, args);

  CHECK(result.isValid());
  CHECK_EQUAL(12, (int)result)

}


UNITTEST(ReflectOneArgumentNonVoidReturnType){

  struct A{
    DS_CLASS(A);
    DS_REFLECTION_METHOD(testMethod);
    virtual int testMethod(int i){
      return 40;
    };
  }a;


  auto type = type_of(a);
  auto method = (const MethodInfo*)type->getMember("testMethod");
  CHECK(method);

  int arg[1] ={ 1};
  auto result = method->call(&a,arg);
  CHECK(result.isValid());
  CHECK_EQUAL(40,(int)result);
}

UNITTEST(ReflectZeroArgumentsNonVoidReturnType){
  struct A{
    DS_CLASS(A);
    DS_REFLECTION_METHOD(testMethod);
    int testMethod(){
      return 31;
    }
  }uut;
  auto type = type_of(uut);
  auto method = (const MethodInfo*)type->getMember("testMethod");
  auto result = method->call(&uut);
  CHECK(result.isValid());
  CHECK_EQUAL(31,(int)result);
}

UNITTEST(ReflectZeroArgumentMethodVoidReturnType){
  static bool called = false;
  struct A{
    DS_CLASS(A);
    DS_REFLECTION_METHOD(testMethod);
    void testMethod(){
      called =true;
    }
  }uut;
  auto type = type_of(uut);
  auto method = (const MethodInfo*)type->getMember("testMethod");
  CHECK(!called)
    auto result = method->call(&uut);
  CHECK(called);
  CHECK(result.isValid());
}


UNITTEST(ReflectTwoArgumentMethodVoidReturnType){

  static bool called = false;
  static std::string str;
  struct A{
    DS_CLASS(A);
    DS_REFLECTION_METHOD(testMethod);
    void testMethod(int i, std::string s){
      str = DS_INLINE_STRING(s<<i);
      called =true;
    }
  }uut;
  auto type = type_of(uut);
  auto method = (const MethodInfo*)type->getMember("testMethod");
  CHECK(!called);
  Argument args[]={5,std::string("hahaha")};
  auto result = method->call(&uut,args);
  CHECK(called);
  CHECK_EQUAL("hahaha5",str);
  CHECK(result.isValid());
}





#include <core.testing.h>

using namespace nspace;
using namespace std;

UNITTEST(MethodInfoMetaDataConst){
  setTestDescription("Tests whether the const flag is properly set for Method info");
  struct A{
    reflect_type(A);
    reflect_method(a);
    reflect_method(b);
    reflect_method(c);
    reflect_method(d);
    reflect_method(e);
    reflect_method(f);
    void a()const{}
    void b(){}
    void c(int)const{}
    void d(int){}
    int e()const{return 0;}
    int f(){return 0;}
  }instance;// one instance is needed else reflection will not be initialized for the class
  // get type
  auto type =type_of(instance);
  auto a = type->getMethod("a");
  auto b = type->getMethod("b");
  auto c = type->getMethod("c");
  auto d = type->getMethod("d");
  auto e = type->getMethod("e");
  auto f = type->getMethod("f");

  CHECK(a->getIsConst());
  CHECK(!b->getIsConst());
  CHECK(c->getIsConst());
  CHECK(!d->getIsConst());
  CHECK(e->getIsConst());
  CHECK(!f->getIsConst());

}


UNITTEST(virtualMethodReflection1){
  struct A{
    reflect_type(A);

    reflect_method(testMethod1);
    virtual void testMethod1(){};
  }a;

  struct B : public A{
    reflect_type(B);
    SUBCLASSOF(A);

    reflect_method(testMethod1);
    void testMethod1(){}
  }b;

  auto typeB = type_of<B>();
  auto method = type_of<B>()->getMethod("testMethod1");


  CHECK(method);
  auto type= method->getOwningType();
  CHECK(type);
  auto name = type->getName();
  CHECK_EQUAL("A",name);


}

UNITTEST(methodReflectionReturnType){
  struct A{
    reflect_type(A);

    reflect_method(test);
    std::string test(){return "";}
  }a;

  auto type = type_of(a);
  auto method = type->getMethod("test");
  auto returntype = method->getReturnType();
  CHECK(returntype!=0);
  CHECK_EQUAL("std::string",returntype->getName());
}
UNITTEST(methodReflectionARgumentList){
  struct A{
    reflect_type(A);

    reflect_method(test);
    void test(int,double,std::string,A){}
  }a;
  // get argument types by reflection
  auto argumentTypes = type_of(a)->getMethod("test")->getArgumentTypes();

  CHECK_EQUAL(4,argumentTypes.size());
  CHECK_EQUAL(argumentTypes[0], typeof(int));
  CHECK_EQUAL(argumentTypes[1], typeof(double));
  CHECK_EQUAL(argumentTypes[2], typeof(std::string));
  CHECK_EQUAL(argumentTypes[3], typeof(A));

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
  auto method = type->getMethod("testMethod");
  CHECK(!called);
  Argument args[]={5,std::string("hahaha")};
  auto result = method->call(&uut,args);
  CHECK(called);
  CHECK_EQUAL("hahaha5",str);
  CHECK(result.isValid());
}




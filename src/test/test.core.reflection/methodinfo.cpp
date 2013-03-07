#include <core.testing.h>

using namespace nspace;
using namespace std;

TEST(1, CallInheritedMember){
  struct A{
    reflect_type(A);
  public:
    A():val(23){}
    // add a field so that pointer offset of b is != 0
    int val;
    int method(){return val;}
    reflect_method(method);

  };
  struct B:public A{
    reflect_type(B);
    reflect_superclasses(A);
  public:
    B():c(29){}
    // add a field so that pointer offset of b is != 0
    int c;
    int method2(){return c;}
    reflect_method(method2);
  }b;

  CHECK(b.method2()==29);
  CHECK(b.method()==23);

  auto inheritedMethod = type_of(b)->getMethod("method");
  CHECK(inheritedMethod);

  CHECK((int)inheritedMethod->call(&b)==23);
   

}


TEST(1, CallOverridenMethod){
  struct A{
    reflect_type(A);
  public:
    A():val(23){}
    // add a field so that pointer offset of b is != 0
    int val;
    virtual int method(){return val;}
    reflect_method(method);

  };
  struct B:public A{
    reflect_type(B);
    reflect_superclasses(A);
  public:
    B():c(29){}
    // add a field so that pointer offset of b is != 0
    int c;
    int method(){return c;}
  }b;

  CHECK(b.method()==29);

  auto inheritedMethod = type_of(b)->getMethod("method");
  CHECK(inheritedMethod);
  CHECK((int)inheritedMethod->call(&b)==29);
   

}

TEST(2, CallOverridenMethod){
  struct A{
    reflect_type(A);
  public:
    A():val(23){}
    // add a field so that pointer offset of b is != 0
    int val;
    virtual int method(){return val;}
    reflect_method(method);

  };
  struct B:public A{
    reflect_type(B);
    reflect_superclasses(A);
  public:
    B():c(29){}
    // add a field so that pointer offset of b is != 0
    int c;
    int method(){return c;}
  }b;
  // cast b to an A pointer
  A * a =&b;
  CHECK(a->method()==29);
  auto inheritedMethod = type_of<A>()->getMethod("method");
  CHECK(inheritedMethod);
  CHECK((int)inheritedMethod->call(a)==29);
   

}

TEST(3, CallOverridenMethod){
  setTestDescription("checks if calls work for virtual inheritance and virtual methods");
  struct A{
    reflect_type(A);
  public:
    A():val(23){}
    // add a field so that pointer offset of b is != 0
    int val;
    virtual int method(){return val;}
    reflect_method(method);

  };
  struct B:public virtual A{
    reflect_type(B);
    reflect_superclasses(A);
  public:
    B():c(29){}
    // add a field so that pointer offset of b is != 0
    int c;
    int method(){return c;}
  }b;
  // cast b to an A pointer
  A * a =&b;
  CHECK(a->method()==29);
  auto inheritedMethod = type_of<A>()->getMethod("method");
  CHECK(inheritedMethod);
  CHECK((int)inheritedMethod->call(a)==29);
   

}



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



UNITTEST(PointerReturnType){
  static int * expected = 0;
  struct A{
    reflect_type(A);

    reflect_method(testMethod)
    std::shared_ptr<int> testMethod(){
      static std::shared_ptr<int> result(new int(43));
       expected=result.get();
      return result;
    }
    
  }a;

  auto type= type_of(a);
  auto method = type->getMethod("testMethod");

  auto result = method->call(&a);
  auto actual = (std::shared_ptr<int>)result;
  CHECK_EQUAL(expected,actual.get());
}

template<typename T>
struct remove_pointers{
  typedef T type;
};

template<typename T>
struct remove_pointers<T*>{
  typedef typename remove_pointers<T>::type type;
};



UNITTEST(remove_pointers){
  typedef char * * * * uut;
  typedef remove_pointers<uut>::type actual;
  typedef char expected;
  CHECK_TYPES(expected,actual);
}
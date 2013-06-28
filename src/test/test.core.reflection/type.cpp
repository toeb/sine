#include <core.testing.h>

using namespace std;
using namespace nspace;


UNITTEST(DereferencePointer){
  //setup
  int * value = new int(3);
  auto type = type_of<decltype(value)>();
  Argument arg = value;
  //act

  Argument dereferenced = type->dereference(arg);
  int result = dereferenced;
  //check

  CHECK(dereferenced.isValid());
  CHECK_EQUAL(type->removePointer(), dereferenced.type);
  CHECK_EQUAL(3,result);
  //cleanup
  delete value;
}


UNITTEST(DereferencePointerPointer){
  //setup
  int * value = new int(3);
  int ** value2 = & value;
  auto type2 = type_of<decltype(value2)>();
  auto type = type_of<decltype(value)>();
  Argument arg2 = value2;
  Argument arg = value;
  //act

  Argument dereferenced2 = type2->dereference(arg2);
  Argument dereferenced = type->dereference(dereferenced2);
  int result = dereferenced;
  //check

  CHECK(dereferenced.isValid());
  CHECK_EQUAL(type->removePointer(), dereferenced.type);
  CHECK_EQUAL(3,result);
  //cleanup
  delete value;
}

UNITTEST(AutoNamespaceTypeConstruction1){
  class Derived{

  };
  auto a = nspace::core::reflection::builder::reflect<Derived>()
    ->fullyQualifiedName("::std1::Derived")
    ->publish()
    ->end();
  


  CHECK_EQUAL(a,nspace::core::reflection::findScope("::std1::Derived"));
  CHECK(contains(nspace::core::reflection::Global()->ChildScopes(), a->getScope()));
}






UNITTEST(RemoveConst){
  auto type = typeof(const int);
  auto noConst = type->removeConst();
  CHECK_EQUAL(typeof(int), noConst);
}
UNITTEST(RemovePointer){
  auto type = typeof(int *);
  auto noPointer = type->removePointer();
  CHECK_EQUAL(typeof(int), noPointer);
}
UNITTEST(RemoveReference){
  auto type = typeof(int *);
  auto noReference = type->removePointer();
  CHECK_EQUAL(typeof(int), noReference);
}

struct A{
  reflect_type(A);
};

UNITTEST(MultiModifierTypeName){

  auto uut = typeof(A const  * const * const&  );
  auto name = uut->getName();
  CHECK_EQUAL("A const * const * const &",name);
}

UNITTEST(ConstVolatileType){
 
 auto t = typeof(const volatile A); 
 auto t2 = t->getUnderlyingType();

 CHECK(t2==typeof(A));
 CHECK(!t->getIsReference());
 CHECK(!t->getIsPointer());
 CHECK(t->getIsConst());
 CHECK(t->getIsVolatile());
}
UNITTEST(volatileType){
 auto t = typeof(volatile A); 
 auto t2 = t->getUnderlyingType();

 CHECK(t2==typeof(A));
 CHECK(!t->getIsReference());
 CHECK(!t->getIsPointer());
 CHECK(!t->getIsConst());
 CHECK(t->getIsVolatile());
}
UNITTEST(referenceType){
 
 auto t = typeof(A&); 
 auto t2 = t->getUnderlyingType();

 CHECK(t2==typeof(A));
 CHECK(t->getIsReference());
 CHECK(!t->getIsPointer());
 CHECK(!t->getIsConst());
 CHECK(!t->getIsVolatile());
}
UNITTEST(pointerType){
 auto t = typeof(A*); 
 auto t2 = t->getUnderlyingType();

 CHECK(t2==typeof(A));
 CHECK(!t->getIsReference());
 CHECK(t->getIsPointer());
 CHECK(!t->getIsConst());
 CHECK(!t->getIsVolatile());

}
UNITTEST(constType){
 auto t = typeof(const A); 
 auto t2 = t->getUnderlyingType();

 CHECK(t2==typeof(A));
 CHECK(!t->getIsReference());
 CHECK(!t->getIsPointer());
 CHECK(t->getIsConst());
 CHECK(!t->getIsVolatile());

}


UNITTEST(type_of1){
  auto type  = type_of<A>();
  CHECK(type);
  CHECK_EQUAL("A", type->getName());
}


UNITTEST(type_ofInstance){
  A a;
  auto type = type_of(a);
  CHECK(type);
  CHECK_EQUAL("A", type->getName());


}

TEST(1,ConstructionViaType){
  static bool defaultCalled=false;
  static int intCalled=0;
  static int instanceCount=0;
  struct A{
    reflect_type(A);
    reflected_default_constructor(public: A){
      defaultCalled=true;
      instanceCount++;
    }
    reflected_constructor(public: A,int i){
      intCalled = i;
      instanceCount++;
    }
  }a;
  auto & t = *type_of(a);

  auto c =t();
  CHECK(defaultCalled)
  auto b = t(5);
  CHECK_EQUAL(5,intCalled);
  CHECK_EQUAL(3,instanceCount);
}
TEST(2, ConstructViaAutoDefaultConstructor){
  
  auto &t = *typeof(int);
  auto result = t();
  CHECK(result.isValid());


};
TEST(3,ConstructViaDefautConstructor){
  auto & t = *typeof(std::string);
  auto result = t();
  CHECK(result.isValid());
  std::shared_ptr<std::string> str=result;
  CHECK((bool)str);
  CHECK_EQUAL(0,str->size());
};




TEST(1, subclassOf){
  struct A{
    reflect_type(A);
  };
  struct A2{
    reflect_type(A2)
  };
  struct B:public A,public A2{    
    reflect_type(A);
    reflect_superclasses(A,A2)

  };
  struct C:public B{
    reflect_type(A);
    reflect_superclasses(B)

  }c;
  auto result = nspace::subclassof<A,C>();
  CHECK(result);

  result = nspace::subclassof<A>(c);
  CHECK(result);
}

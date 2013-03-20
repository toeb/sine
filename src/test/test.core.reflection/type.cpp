#include <core.testing.h>

using namespace std;
using namespace nspace;



UNITTEST(Construction1){
  struct Derived:public Type{
    Derived():Type("____testtype",0){}
  }uut;
  
  CHECK_EQUAL("____testtype",uut.getFullyQualifiedName());
  CHECK_EQUAL("____testtype",uut.getName());
  CHECK_EQUAL(&uut,uut.getUnderlyingType());
  CHECK_EQUAL(&uut,uut.getUnqualifiedType());
  CHECK_EQUAL(NamespaceInfo::Global(),uut.getNamespace());

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


UNITTEST(MultiModifierTypeName){
  struct A{
    reflect_type(A);
  };

  auto uut = typeof(A const  * const * const&  );
  auto name = uut->getName();
  CHECK_EQUAL("A const * const * const &",name);
}

UNITTEST(ConstVolatileType){
 struct A{
   reflect_type(A);
 };
 
 auto t = typeof(const volatile A); 
 auto t2 = t->getUnderlyingType();

 CHECK(t2==typeof(A));
 CHECK(!t->getIsReference());
 CHECK(!t->getIsPointer());
 CHECK(t->getIsConst());
 CHECK(t->getIsVolatile());
}
UNITTEST(volatileType){
 struct A{
   reflect_type(A);
 };
 
 auto t = typeof(volatile A); 
 auto t2 = t->getUnderlyingType();

 CHECK(t2==typeof(A));
 CHECK(!t->getIsReference());
 CHECK(!t->getIsPointer());
 CHECK(!t->getIsConst());
 CHECK(t->getIsVolatile());
}
UNITTEST(referenceType){
 struct A{
   reflect_type(A);
 };
 
 auto t = typeof(A&); 
 auto t2 = t->getUnderlyingType();

 CHECK(t2==typeof(A));
 CHECK(t->getIsReference());
 CHECK(!t->getIsPointer());
 CHECK(!t->getIsConst());
 CHECK(!t->getIsVolatile());
}
UNITTEST(pointerType){
 struct A{
   reflect_type(A);
 };
 
 auto t = typeof(A*); 
 auto t2 = t->getUnderlyingType();

 CHECK(t2==typeof(A));
 CHECK(!t->getIsReference());
 CHECK(t->getIsPointer());
 CHECK(!t->getIsConst());
 CHECK(!t->getIsVolatile());

}
UNITTEST(constType){
 struct A{
   reflect_type(A);
 };
 
 auto t = typeof(const A); 
 auto t2 = t->getUnderlyingType();

 CHECK(t2==typeof(A));
 CHECK(!t->getIsReference());
 CHECK(!t->getIsPointer());
 CHECK(t->getIsConst());
 CHECK(!t->getIsVolatile());

}


UNITTEST(type_of1){
  struct A{
    reflect_type(A);
  };

  auto type  = type_of<A>();
  CHECK(type);
  CHECK_EQUAL("A", type->getName());
}


UNITTEST(type_ofInstance){
  struct A{
    reflect_type(A);  
  }a;

  auto type = type_of(a);
  CHECK(type);
  CHECK_EQUAL("A", type->getName());


}



TEST(1, defaultConstructor1){
  FAIL("not implemented");
}

TEST(2, defualtConstructor2){
  
  FAIL("not implemented");

}


TEST(3, defualtConstructor3){
  
  FAIL("not implemented");
}



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

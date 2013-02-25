#include <core.testing.h>

using namespace std;
using namespace nspace;




namespace nspace{
  
  template<typename T>
  struct  TypeInfo<T&>:public Type{
    TEMPLATEDSINGLETON(TypeInfo,<T&>){
      setName("&");
      setIsReference(true);
      auto type = type_of<T>();
      setUnderlyingType(type);
      setBaseType(type->getBaseType());
    }
   };
   template<typename T>
   struct  TypeInfo<T*>:public Type{
     TEMPLATEDSINGLETON(TypeInfo,<T*>){       
      setName("*");
      setIsPointer(true);
      auto type =  type_of<T>();
      setUnderlyingType(type);
      setBaseType(type->getBaseType());
    }
   };
   template<typename T>
   struct  TypeInfo<const T>:public Type{
     TEMPLATEDSINGLETON(TypeInfo,<const T>){       
      setName("const");
      setIsConst(true);
      auto type =  type_of<T>();
      setUnderlyingType(type);
      setBaseType(type->getBaseType());
    }
   };
   template<typename T>
   struct  TypeInfo<volatile T>:public Type{
     TEMPLATEDSINGLETON(TypeInfo,<volatile T>){
      setName("volatile");
      setIsVolatile(true);
      auto type =  type_of<T>();
      setUnderlyingType(type);
      setBaseType(type->getBaseType());
    }
   };
   template<typename T>
   struct  TypeInfo<const volatile T>:public Type{
     TEMPLATEDSINGLETON(TypeInfo,<const volatile T>){
      setName("const volatile");
      setIsVolatile(true);
      auto type =  type_of<T>();
      setUnderlyingType(type);
      setBaseType(type->getBaseType());
    }
   };


}

UNITTEST(multiType){
  struct A{
    reflect_type(A);
  };

  auto uut = typeof(A const  * const * const&  );

  auto name = uut->fullName();

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



TEST(1, createInstance){
  CHECK( typeof(std::string)->isConstructible());
  auto instance = typeof(std::string)->createTypedInstance<std::string>();  
  CHECK(instance);
  *instance = "asdasdasdasd";
  CHECK_EQUAL("asdasdasdasd",*instance);
}

TEST(2, createInstance){
  struct A{
    int integer;
    std::string text;
    A():integer(123),text("asdf"){

    }
    DS_CLASS(A);

    DS_DEFAULT_CONSTRUCTIBLE;
  }a;// need to instanciate else static code is not executed :(

  CHECK( typeof(A)->isConstructible());

  auto instance = typeof(A)->createTypedInstance<A>();

  CHECK(instance);
  CHECK_EQUAL(123,instance->integer);
  CHECK_EQUAL("asdf",instance->text);

}


TEST(3, createInstance){
  // tests if a instance cannot be created
  // A has no default constructor . hence it cannot be created trivially
  struct A{        
    DS_CLASS(A);
    A(int i){}    
  };

  CHECK( !typeof(A)->isConstructible());
  CHECK(!typeof(A)->createInstance());
}


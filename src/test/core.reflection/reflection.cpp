#include <core.testing.h>

#include <core.reflection.h>


using namespace nspace;
using namespace std;


TEST(1,DS_CLASS){
  // tests weather typeof(A) correctly returns a type
  struct A{
    DS_CLASS(A);
  };
  auto type = typeof(A);
  CHECK(type!=0);
}
TEST(2,DS_CLASS){
  // tests the typeof(...) and getType operation 
  struct A{
    DS_CLASS(A);
  };
  A a;
  auto & type = a.getType();
  CHECK(*typeof(A)==type);
}
TEST(3,DS_CLASS){
  // this tests whether the Derived class correctly overrides 
  // the base classes getType() method
  struct Base{
    DS_CLASS(Base)
  }base;
  struct Derived : public Base{
    DS_CLASS(Derived)
  }derived;
  auto & baseType = base.getType();
  auto & derivedType = derived.getType();
  
  CHECK(baseType != derivedType);
}
TEST(4,DS_CLASS){
  // this tests whether the Derived class still functions when not parttaking in reflection
  // the base classes getType() method
  struct Base{
    DS_CLASS(Base)
  }base;
  
  struct HiddenDerived : public Base{

  }hidden;
  auto & baseType = base.getType();
  auto & derivedType = hidden.getType();
  
  CHECK_EQUAL(baseType , derivedType);
}


TEST(3,HierarchyObject){
  // tests weather the converiosn to Object was correct
  struct A:public Object{
    DS_CLASS(A);
  }a;
}

TEST(2,HierarchyObject){
  // tests whether the IsConvertibleToObject property is set correctly
  struct A : public Object{
    DS_CLASS(A);
  }a;
  auto type = typeof(A);

  CHECK(!typeof(A)->getIsConvertibleToObject());
}


TEST(1,HierarchyObject){
  struct A : public Object{
    DS_CLASS(A);
    DS_HIERARCHY_OBJECT
  }a;
  struct B : public A{
    DS_CLASS(B);
    DS_HIERARCHY_OBJECT
  }b;
  auto typeA= typeof(A);
  auto typeB = typeof(B);

  CHECK(typeof(A)->getIsConvertibleToObject());
  CHECK(typeof(B)->getIsConvertibleToObject());
  void * v = &b;

  auto o = typeof(B)->toObjectPointer(v);



}

TEST(1, createInstance){
  CHECK( typeof(std::string)->getIsConstructible());
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

  CHECK( typeof(A)->getIsConstructible());

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

  CHECK( !typeof(A)->getIsConstructible());
  CHECK(!typeof(A)->createInstance());
}




#ifdef NEWIMPL
#include <core/template/meta_type_construction.h>
#include <core/template/meta_type_name.h>
#include <core/template/meta_type_tostring.h>


TEST(1,typeNameOf){
  struct A{
    DS_CLASS(A);
  };

  auto name = meta_type_name<A>::value();
  CHECK_EQUAL("A",name);

}

TEST(2,typeNameOf){
  
  auto name = meta_type_name<std::string>::value();
  CHECK_EQUAL("std::string",name);
}

TEST(3,typeNameOf){
  auto name = meta_type_name<bool>::value();
  CHECK_EQUAL("bool",name);
}



TEST(1, createInstance){


  CHECK( typeof(std::string)->getIsConstructible());

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
    
  };

  CHECK( typeof(A)->getIsConstructible());

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

  CHECK( !typeof(A)->getIsConstructible());
  CHECK(!typeof(A)->createInstance());
}



TEST(4,createInstance){
  // tests whether the singlton instance can be created
  struct A{
    DS_CLASS(A)
    SINGLETON(A){
      text = "TEXTVALUE";
    }
    std::string text;
  };
  CHECK(typeof(A)->getIsConstructible());

  auto instance = typeof(A)->createInstance();
  CHECK_EQUAL(instance.get(), A::instance().get());


}
#endif
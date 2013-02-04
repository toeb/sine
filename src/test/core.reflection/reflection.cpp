#include <core.testing.h>

#include <core.reflection.h>


using namespace nspace;
using namespace std;


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
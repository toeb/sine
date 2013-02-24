#include <core.testing.h>

using namespace std;
using namespace nspace;




namespace nspace2{


}

UNITTEST(referenceType){
 
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


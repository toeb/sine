#include <core.testing.h>

using namespace std;
using namespace nspace;




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
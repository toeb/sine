#include <CppUnitLite/TestHarness.h>
#include <core/Object.h>
#include <core/NamedObject.h>

#include <string>
using namespace nspace;
using namespace std;
TEST(Create, Object){
  Object o;
  CHECK(o.getType()==Object::ClassType());
  
}

TEST(Create1, NamedObject){
  NamedObject o;
  CHECK(o.name()==NamedObject::DefaultName);

}
TEST(Create2, NamedObject){
  NamedObject o("testname");
  CHECK(o.name()=="testname");

}



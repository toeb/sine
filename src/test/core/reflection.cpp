#include <CppUnitLite/TestHarness.h>
#include "conversion.h"
#include <core/Object.h>
#include <core/PropertyChangingObject.h>
#include <core/Reflection.h>

#include <string>
#include <sstream>
using namespace nspace;
using namespace std;





TEST(Create, Prop){
  class TestClass{
  public:
    TestClass():_IntegerProperty(0){}
    SIMPLE_PROPERTY(int, IntegerProperty){
      if(newvalue > oldvalue +4)cancel = true;
    }
  }a;
  CHECK_EQUAL(0,a.getIntegerProperty());
  a.setIntegerProperty(3);
  CHECK_EQUAL(3,a.getIntegerProperty());
  a.setIntegerProperty(20);
  CHECK_EQUAL(3,a.getIntegerProperty());
}


TEST(Test1, PropertyChanging){
  class TestClass : public PropertyChangingObject{
  public:
    TestClass():_IntegerProperty(0){}
    NOTIFYING_PROPERTY(int, IntegerProperty){
      if(newvalue > oldvalue +4)cancel = true;
    }
  }a;
  CHECK_EQUAL(0,a.getIntegerProperty());
  a.setIntegerProperty(3);
  CHECK_EQUAL(3,a.getIntegerProperty());
  a.setIntegerProperty(20);
  CHECK_EQUAL(3,a.getIntegerProperty());

  bool success = false;
  std::string name;
  DelegatePropertyChangedListener listener([&name, &success](Object * object,const std::string & prop){
    name = prop;
    if(prop=="IntegerProperty")success = true;
  });

  a.listeners()|=&listener;

  a.setIntegerProperty(3);
  CHECK(!success);
  a.setIntegerProperty(4);

  CHECK(name=="IntegerProperty");
  CHECK(success);
}

class TestClass2{
  REFLECTABLE_OBJECT(TestClass2);
public:
  TestClass2():_IntegerProperty(0){}
  REFLECTABLE_PROPERTY(int, IntegerProperty){
    if(newvalue > oldvalue +4)cancel = true;
  }
};
TEST(Test1, Reflection){
  TestClass2 a;
  CHECK_EQUAL(0,a.getIntegerProperty());
  a.setIntegerProperty(3);
  CHECK_EQUAL(3,a.getIntegerProperty());
  a.setIntegerProperty(20);
  CHECK_EQUAL(3,a.getIntegerProperty());
  
  auto prop =a.getProperty("IntegerProperty");

  CHECK(prop!=0);
  CHECK(prop->getPropertyName()=="IntegerProperty");
  CHECK_EQUAL(3,a.getPropertyValue<int>("IntegerProperty"));
  a.setPropertyValue("IntegerProperty",5);
  CHECK_EQUAL(5,a.getIntegerProperty());
  CHECK(a.getProperty("notexisting")==0);
}




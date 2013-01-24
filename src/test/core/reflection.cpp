#include <core.testing.h>
#include "conversion.h"
#include <core.h>

#include <string>
#include <sstream>
using namespace nspace;
using namespace std;



class Tmp : public virtual PropertyChangingObject{
  REFLECTABLE_OBJECT(Tmp);
  PROPERTY(int,IntValue){}
  PROPERTY(std::string,StringValue){}
};
void testAdapter1(){
  Tmp t;
  PropertyAdapter adapter1(&t,"IntValue");
  PropertyAdapter adapter2(&t, "StringValue");
  auto observer = new DelegateObjectObserver<std::function<void (Observable *)>>([](Observable* observable){
    auto a = dynamic_cast<PropertyAdapter*>(observable);
    if(!a)return ; //fail
    std::cout << a->getPropertyInfo()->getName() << " changed to ";
    a->serialize(std::cout);
    cout << endl;
  });
  adapter1.addObjectObserver(observer);
  adapter2.addObjectObserver(observer);


  t.setIntValue(3);
  t.setStringValue("Lol");


  adapter1.set(42);

}

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

class TestClass2 : public virtual PropertyChangingObject{
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
  CHECK(prop->getName()=="IntegerProperty");
  CHECK_EQUAL(3,a.getPropertyValue<int>("IntegerProperty"));
  a.setPropertyValue("IntegerProperty",5);
  CHECK_EQUAL(5,a.getIntegerProperty());
  CHECK(a.getProperty("notexisting")==0);
}




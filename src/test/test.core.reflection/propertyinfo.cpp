#include <core.testing.h>
#include <core.reflection.h>
#include <memory>
using namespace nspace;


TEST(1, propertyTest){
  struct A{
    reflect_type(A);
    int prop()const{return 1;}
    void setProp(const int i){};


    reflect_property(Prop,prop,setProp)

    //reflect_property(prop, setProp);
  };

  A a;
  auto type = typeof(A);
  auto prop = dynamic_cast<const PropertyInfo*>(type->getMember("Prop"));
 auto result = (int)prop->get(&a);
 CHECK(result==1);
}
namespace testNamespace{
  struct A{
    reflect_type(A);
  public:
    typedef int reflect_property(TestProperty);

  public:
    typedef int * reflect_property(TestPropertyTwo);
  public:
    typedef std::shared_ptr<double> reflect_property(TestPropertyThree);

    
  public:
    A():_TestProperty(3),_TestPropertyTwo(new int(3232)){}
  };

TEST(Gettable,PropertyInfo){
  A a;
  auto property = (const PropertyInfo*)typeof(A)->getMember("TestProperty");  
  CHECK(property->isGettable());  
}

TEST(Settable,PropertyInfo){
  A a;
  auto property = (const PropertyInfo*)typeof(A)->getMember("TestProperty");
  CHECK(property->isSettable());
}
TEST(GetValue,PropertyInfo){
  A a;
  auto prop = (const PropertyInfo*)typeof(A)->getMember("TestProperty");
  CHECK_EQUAL(3,(int)prop->get(&a));
}

TEST(SetValue, PropertyInfo){
  A a;
  auto prop = (const PropertyInfo*)typeof(A)->getMember("TestProperty");
  prop->set(&a,88);
  CHECK(88, a.getTestProperty());
}


TEST(GetPointerValue,PropertyInfo){
  A a;
  auto prop = (const PropertyInfo*)typeof(A)->getMember("TestPropertyTwo");
  auto val = (int*)prop->get(&a);
  CHECK_EQUAL(3232,*val);
}

TEST(GetSmartPointer,PropertyInfo){
  A a;
  std::shared_ptr<double> thePointer(new double(141));
  a.setTestPropertyThree(thePointer);
  
  auto prop = (const PropertyInfo*)typeof(A)->getMember("TestPropertyThree");  
  auto val = (std::shared_ptr<double>) prop->get(&a);
  CHECK(141,*val);
}

TEST(GetOwningType,PropertyInfo){
  A a;
  auto prop = typeof(A)->getProperty("TestProperty");
  auto owningType=prop->getOwningType();
  CHECK_EQUAL(typeof(A),owningType);
}

TEST(GetPropertyType1,PropertyInfo){
  A a;
  auto prop = typeof(A)->getProperty("TestProperty");
  auto propType = prop->getPropertyType();
  CHECK_EQUAL(typeof(int),propType);
}

TEST(GetPropertyType2,PropertyInfo){
  A a;
  auto prop = typeof(A)->getProperty("TestPropertyThree");
  auto propType = prop->getPropertyType();
  CHECK_EQUAL(typeof(std::shared_ptr<double>),propType);
}

}


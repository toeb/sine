#include <core.testing.h>

#include <core.reflection.h>
#include <core.reflection/dynamic/DynamicObject.h>
#include <core.reflection/dynamic/DynamicReflectedObjectImplementation.h>

using namespace nspace;



namespace test{



  class TestClass{
    reflect_type(TestClass);

    typedef std::string reflect_property(LastName);

    reflect_method(increment);
    int increment(int i){return i+1;}

    reflect_method(__get_property);
    Argument __get_property(const std::string & name){
      if(name=="DynamicProperty"){
        return Argument(5);
      }
      return Argument();
    }
    reflect_method(__set_property);
    bool __set_property(const std::string & name, Argument argument){
      return false;
    }

  };
  UNITTEST(DynamicObjectArgumentConvertion){
    // create a object (as shared pointer)
    auto subject = std::make_shared<TestClass>();
    // create the dynamic object
    DynamicObject uut = make_dynamic(subject);
    
    // get handle from object
    auto handle = *uut;

    CHECK_EQUAL(subject.get(),handle.data.get());

  }

  UNITTEST(DynamicObjectReflectedPropertyAccess){
    // this test tries to get the property "LastName" which is reflectable.

    // create object
    auto subject = std::make_shared<TestClass>();
    subject->setLastName("Becker");

    // create dynamic object
    DynamicObject uut=make_dynamic(subject);

    // get Property 
    auto property =uut["LastName"].get();


    CHECK(property.isValid());
    CHECK_EQUAL(typeof(std::string),property.type);
    CHECK_EQUAL(std::string("Becker"),(std::string)property);
  }

  UNITTEST(DynamicObjectReflectedPropertySet){
    //this test tries to set the property value for the reflected property "LastName"

    // create object
    auto subject = std::make_shared<TestClass>();

    // create dynamic object
    DynamicObject uut = make_dynamic(subject);

    //setproperty
    uut["LastName"].set(std::string("Beeker"));

    CHECK_EQUAL(std::string("Beeker"), subject->getLastName());

  }

  UNITTEST(DynamicObjectDynamicPropertyAccess){
    //this test tries to set and get a property which
    auto subject = std::make_shared<TestClass>();

    DynamicObject uut = make_dynamic(subject);

    int result = uut["DynamicProperty"].get();
    CHECK_EQUAL(5,result);
  }

  UNITTEST(DynamicObjectDynamicPropertyAccessSet){
    DynamicObject uut = make_dynamic_mapped();

    uut["propA"].set(3434);

    int result = uut["propA"].get();

    CHECK_EQUAL(3434,result);

  }

  UNITTEST(DynamicObjectGetNonExistingProperty){
    auto uut = make_dynamic_mapped();
    Argument result = uut["propA"].get();
    CHECK(!result.isValid());
  }
}
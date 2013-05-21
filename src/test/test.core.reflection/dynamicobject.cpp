#include <core.testing.h>

#include <core.reflection.h>
#include <core.reflection/dynamic/DynamicObject.h>
#include <core.reflection/dynamic/DynamicReflectedObjectImplementation.h>

using namespace nspace;



namespace test{


  // class used for testing purposes
  class TestClass{
    reflect_type(TestClass);

    typedef std::string reflect_property(LastName);    
    typedef int reflect_property(Age);

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

    reflect_method(__list_property_names);
    std::vector<std::string> __list_property_names()const{
      std::vector<std::string> result;
      result.push_back("DynamicProperty");
      return result;
    }

  };
  
  bool copy(DynamicObject & destination, const DynamicObject & source){
    auto names = concat(source.getPropertyNames(),destination.getPropertyNames());
    std::sort(std::begin(names),std::end(names));
    names.erase(std::unique(std::begin(names),std::end(names)),std::end(names));

    
    for(auto it = std::begin(names); it != std::end(names); it++){
      auto d = destination.getProperty(*it);
      auto s = source.getProperty(*it);
      auto value = s->get();
      if(!value.isValid())continue;
      d->set(value);
    }

    return true;
  }

  UNITTEST(CopyReflectedObjectToMappedObject){
    auto subject1 = std::make_shared<TestClass>();
    subject1->setAge(23);
    subject1->setLastName("Becker");
    
    auto uut1 = make_dynamic(subject1);      
    auto uut2 = make_dynamic_mapped();

    // act
    auto success = copy(uut2,uut1);

    // validate
    CHECK(success);
    CHECK(uut2.hasProperty("LastName"));
    CHECK_EQUAL(std::string("Becker"), (std::string)uut2["LastName"].get());
    CHECK_EQUAL(5,(int)uut2["DynamicProperty"]);
    CHECK_EQUAL(23,(int)uut2["Age"]);





  }

  UNITTEST(CopyDynamicObjectToSameUnderylingType1){
    // this test only checks reflected properties - no dynamic properties
    auto subject1 = std::make_shared<TestClass>();
    subject1->setAge(24);
    subject1->setLastName("Becker");
    auto subject2 = std::make_shared<TestClass>();

    auto uut1 = make_dynamic(subject1);
    auto uut2 = make_dynamic(subject2);

    // copy uut1 to uut2 propertywise
    auto result = copy(uut2,uut1);
    
    CHECK(result)

    CHECK_EQUAL(24,subject2->getAge());
    CHECK_EQUAL("Becker",subject2->getLastName());


  }
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
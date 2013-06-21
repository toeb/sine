#include <core.testing.h>

#include <utility.serialization.json.h>


#include <core.reflection.h>
using namespace nspace;
using namespace nspace::core::serialization;



UNITTEST(EmptyInput){
  // setup
  std::string json ="";
  JsonDeserializer deserializer;
  
  //act
  auto result =  deserializer.deserialize(json);
  
  // validate
  CHECK(!result.isValid());
}

UNITTEST(DeserializeInt){
  // setup
  std::string json = "-321"; 
  JsonDeserializer deser;
  // act
  auto result = deser.deserialize(json);
  // validate
  CHECK(result.isValid());
  CHECK(result.type == typeof(int));
  CHECK_EQUAL(-321, (int)result);
}

UNITTEST(DeserializeUint){
  //setup
  std::string json = "u123123";
  JsonDeserializer deser;

  //act
  auto result = deser.deserialize(json);

  //validate  
  CHECK(result.isValid());
  CHECK(result.type == typeof(unsigned int));
  CHECK_EQUAL(123123, (unsigned int)result);
}

UNITTEST(DeserializeStdString){
  //setup
  std::string json = "\"hello from json\"";
  JsonDeserializer deser;

  //act
  auto result = deser.deserialize(json);

  //validate  
  CHECK(result.isValid());
  CHECK(result.type == typeof(std::string));
  CHECK_EQUAL("hello from json", (std::string)result);
}


UNITTEST(SerializeInt){
  //setup
  int value = -321;
  JsonSerializer ser;
  JsonDeserializer deser;
  
  //act
  auto json = ser.serialize(value);
  auto result = deser.deserialize(json);
  
  //validate
  CHECK(result.isValid());
  CHECK_EQUAL(typeof(int),result.type );
  CHECK_EQUAL(value, (int)result);
}
UNITTEST(SerializeStdString){
  
  //setup
  std::string value = "serialized value!";
  JsonSerializer ser;
  JsonDeserializer deser;
  
  //act
  auto json = ser.serialize(value);
  auto result = deser.deserialize(json);
  
  //validate
  CHECK(result.isValid());
  CHECK_EQUAL(typeof(std::string),result.type);
  CHECK_EQUAL(value, (std::string)result);
}
UNITTEST(SerializeUint){
  //setup
  unsigned int value = 333;
  JsonSerializer ser;
  JsonDeserializer deser;
  
  //act
  auto json = ser.serialize(value);
  auto result = deser. deserialize(json);
  
  //validate
  CHECK(result.isValid());
  CHECK_EQUAL(typeof( unsigned int),result.type);
  CHECK_EQUAL(value, ( unsigned int)result);

}
class TestClass{
  reflect_type(TestClass);
  
  typedef std::string reflect_property(StringProperty);
  typedef int  reflect_property(IntProperty);
  typedef double reflect_property(DoubleProperty);
  typedef std::shared_ptr<int> reflect_property(IntPtrProperty);
  typedef std::shared_ptr<TestClass> reflect_property(TestClassProperty);
};

UNITTEST(SampleClass){
  //setup
  auto sut = std::make_shared<TestClass>();
  sut->setTestClassProperty(sut);
  sut->setDoubleProperty(424.3);
  sut->setIntProperty(1123);
  sut->setStringProperty("hello from string property");
  auto intptr = std::make_shared<int>(2323);
  sut->setIntPtrProperty(intptr);
  JsonSerializer ser;
  //act
  auto json = ser.serialize(sut);

}
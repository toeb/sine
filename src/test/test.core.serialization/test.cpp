#include <core.testing.h>

#include <utility.serialization.json.h>


#include <core.reflection.h>
using namespace nspace;
using namespace nspace::core::serialization;
JsonDeserializer a;
JsonSerializer b;
UNITTEST(GetSerializer1){
  auto serializer = serializerFor("json");
  CHECK((bool)serializer);
}
UNITTEST(GetSerializer2){
  auto serializer = serializerFor("unknown happy format");
  CHECK(!(bool)serializer);
}

UNITTEST(GetDeserializer1){
  auto deserializer = deserializerFor("json");
  CHECK((bool)deserializer);
}
UNITTEST(GetDeserializer2){
  auto deserializer = deserializerFor("unknown happy format");
  CHECK(!(bool)deserializer);
}



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

class TestClass{
  reflect_type(::TestClass);
  reflected_default_constructor(public:TestClass){}
  typedef std::string reflect_property(StringProperty);
  typedef int  reflect_property(IntProperty);
  typedef double reflect_property(DoubleProperty);
  typedef std::shared_ptr<int> reflect_property(IntPtrProperty);
  typedef std::shared_ptr<int> reflect_property(IntPtrProperty2);
  typedef int * reflect_property(UnsafeIntPtr);
  typedef std::shared_ptr<TestClass> reflect_property(TestClassProperty);
  typedef std::vector<int> reflect_property(IntVectorProperty);
  typedef std::vector<std::string> reflect_property(StringVectorProperty);
  typedef std::vector<std::shared_ptr<TestClass>> reflect_property(TestClassVectorProperty);
public: property_reference(TestClassVectorProperty);
};

//instanciate testclass
auto t = type_of<TestClass>();
TestClass t2;

UNITTEST(DeserializeEmptyObjectTypeImplied){
  //setup 
  auto json = "{\"$_id\":1, \"$_t\":\"::TestClass\"}";
  JsonDeserializer deser;
  
  //act
  auto result = deser.deserialize(json);

  //check
  CHECK(result.isValid());
  CHECK_EQUAL(type_of<TestClass>(), result.type);
}



UNITTEST(DeserializeObjectTypeStated){
  //setup 
  auto json = "{}";
  JsonDeserializer deser;
  auto type = typeof(TestClass);
  //act
  auto result = deser.deserialize(json,type);

  //check
  CHECK(result.isValid());
  CHECK_EQUAL(type_of<TestClass>(), result.type);
}


UNITTEST(DeserializeObjectWithPrimitveProperties){
  //setup
  auto json = "{ \"$_t\":\"::TestClass\", \"IntProperty\":323, \"StringProperty\":\"hello from json\"}";
  JsonDeserializer deser;

  // act
  auto result = deser.deserialize(json);
  auto data=result.cast<TestClass>();
  auto intValue = data->getIntProperty();
  auto stringValue =data->getStringProperty();
  //check
  CHECK_EQUAL(323,intValue);
  CHECK_EQUAL("hello from json",stringValue);
}



UNITTEST(DeserializeObjectWithValuePointer){
  //setup
  auto json = "{ \"$_t\":\"::TestClass\", \"IntPtrProperty\":{\"$_id\":1,\"$_value\":323} ,\"IntPtrProperty\":{\"$_id\":1} }";
  JsonDeserializer deser;

  // act
  auto result = deser.deserialize(json);
  auto data=result.cast<TestClass>();
  auto intValue = data->getIntProperty();
  auto stringValue =data->getStringProperty();
  //check
  CHECK_EQUAL(323,intValue);
  CHECK_EQUAL("hello from json",stringValue);
}

UNITTEST(SerializeEmptyObject){
  // setup
  auto sut = std::make_shared<TestClass>();
  JsonSerializer ser;
  //act
  auto json = ser.serialize(sut);
  //check
  CHECK(""!=json);
  
}
UNITTEST(CompleteSerializationExample){
  //setup
  auto sut = std::make_shared<TestClass>();
  auto sut2 = std::make_shared<TestClass>();
  sut->setTestClassProperty(sut);
  sut->setDoubleProperty(424.3);
  sut->setIntProperty(1123);
  sut->setStringProperty("hello from string property");
  auto intptr = std::make_shared<int>(2323);
  sut->setUnsafeIntPtr(intptr.get());
  sut->setIntPtrProperty(intptr);
  sut->setIntPtrProperty2(intptr);
  std::vector<int> listofint;
  listofint.push_back(3);
  listofint.push_back(4);
  listofint.push_back(2);
  listofint.push_back(1);
  sut->setIntVectorProperty(listofint);
  std::vector<std::string> listofstring;
  listofstring.push_back("asdasd");
  listofstring.push_back("asd3asd");
  listofstring.push_back("a4sdasd");
  listofstring.push_back("as2dasd");
  listofstring.push_back("asd1asd");
  sut->setStringVectorProperty(listofstring);
  sut->TestClassVectorProperty().push_back(sut);
  sut->TestClassVectorProperty().push_back(sut);
  sut->TestClassVectorProperty().push_back(sut);
  sut->TestClassVectorProperty().push_back(sut);
  sut->TestClassVectorProperty().push_back(sut);
  sut->TestClassVectorProperty().push_back(sut2);
  
  JsonSerializer ser;
  //act
  auto json = ser.serialize(sut);

}
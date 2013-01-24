#include <core.testing.h>
#include <map>
#include <string>


#define DS_CURRENT_TYPE(CLASSNAME) typedef Person CurrentType;



#define DS_PROPERTY_NAME(NAME) NAME

#define DS_PROPERTY_TYPE_NAME(NAME)  DS_PROPERTY_NAME(NAME)##PropertyType

#define DS_STATIC_TYPE_DEFINITION_HELPER_NAME(NAME) DS_PROPERTY_NAME(NAME)##NullPointer

#define DS_PROPERTY_TYPE_DEFINITION(NAME) private: typedef std::remove_const<std::remove_pointer<decltype(DS_STATIC_TYPE_DEFINITION_HELPER_NAME(NAME)())>::type>::type DS_PROPERTY_TYPE_NAME(NAME); //this is the definition of the property type

#define DS_PROPERTY_DEFINITION(NAME) /* Begginning of Property */\
  static const * DS_STATIC_TYPE_DEFINITION_HELPER_NAME(NAME)(){return 0;}/*this should not create any overhead and is possible for any type*/\
  DS_PROPERTY_TYPE_DEFINITION(NAME) /* Define Property type */

// there can be field storage pointer storage, refence storage and callback storage
// 

#define DS_PROPERTY_STORAGE_NAME(NAME) DS_CONCAT(_, DS_PROPERTY_NAME(NAME))

#define DS_PROPERTY_STORAGE_TYPE_NAME(NAME) DS_PROPERTY_NAME(NAME)##StorageType
#define DS_PROPERTY_STORAGE_TYPE_FIELD(NAME) typedef DS_PROPERTY_TYPE_NAME(NAME) DS_PROPERTY_STORAGE_TYPE_NAME(NAME);
#define DS_PROPERTY_STORAGE_TYPE_POINTER(NAME) typedef std::add_pointer<DS_PROPERTY_TYPE_NAME(NAME)>::type DS_PROPERTY_STORAGE_TYPE_NAME(NAME);
#define DS_PROPERTY_STORAGE_TYPE_REFERENCE(NAME) typedef std::add_reference<DS_PROPERTY_TYPE_NAME(NAME)>::type DS_PROPERTY_STORAGE_TYPE_NAME(NAME);




#define DS_PROPERTY_STORAGE_FIELD(NAME) DS_PROPERTY_STORAGE_TYPE_FIELD(NAME) DS_PROPERTY_STORAGE_TYPE_NAME(NAME) DS_PROPERTY_STORAGE_NAME(NAME);
#define DS_PROPERTY_STORAGE_POINTER(NAME)  DS_PROPERTY_STORAGE_TYPE_POINTER(NAME) DS_PROPERTY_STORAGE_TYPE_NAME(NAME) DS_PROPERTY_STORAGE_NAME(NAME);
#define DS_PROPERTY_STORAGE_REFERENCE(NAME) DS_PROPERTY_STORAGE_TYPE_REFERENCE(NAME) DS_PROPERTY_STORAGE_TYPE_NAME(NAME) DS_PROPERTY_STORAGE_NAME(NAME);
#define DS_PROPERTY_STORAGE_CALLBACK(NAME) 

#define DS_PROPERTY_STORAGE(NAME)

class Person{
private: typedef Person CurrentType;



std::map<std::string, int> static const *__LastName(){return 0;}// this should not create any overhead and is possible for any type
private: typedef std::remove_pointer<decltype(__LastName())>::type PropertyTypeLastName; //this is the definition of the property type
private: PropertyTypeLastName LastName;

private: int _Age;
public: int getAge(){return _Age;}
protected: void setAge(int & value){_Age=value;}
protected: const int & age()const{return _Age;}

bool DS_PROPERTY_DEFINITION(IsAlive);
public: DS_PROPERTY_STORAGE_FIELD(IsAlive);

        std::string DS_PROPERTY_DEFINITION(MiddleNames);
      public: DS_PROPERTY_STORAGE_FIELD(MiddleNames);

              Person DS_PROPERTY_DEFINITION(SpecialOther);
public:   DS_PROPERTY_STORAGE_POINTER(SpecialOther);

              Person DS_PROPERTY_DEFINITION(Self);
public: DS_PROPERTY_STORAGE_REFERENCE(Self);
public:
  Person():_Self(*this),_IsAlive(false){}

};


TEST(1,propertyDefinition){
  struct A{
    std::string DS_PROPERTY_DEFINITION(StringValue)
    friend class UnitTestClass;
  };

  auto result=std::is_same<A::StringValuePropertyType,std::string>::value;
  CHECK(result);
}


TEST(1, propertyField){
  class A{
    std::string DS_PROPERTY_DEFINITION(StringValue)
      DS_PROPERTY_STORAGE_FIELD(StringValue)
    private:
      friend class UnitTestClass;
  };
  auto result=std::is_same<A::StringValuePropertyType,std::string>::value;
  CHECK(result);
}


TEST(1, TemplatedPropertyField){
  class A{
    std::map<std::string,std::string> DS_PROPERTY_DEFINITION(MapValue)
      DS_PROPERTY_STORAGE_FIELD(MapValue);
  private:
    friend class UnitTestClass;
  };
    auto result = std::is_same<A::MapValuePropertyType,std::map<std::string,std::string>>::value;
    CHECK(result);
}


TTEST_DEFAULT(PropertyField, typename PropertyType){
  class A{
    PropertyType DS_PROPERTY_DEFINITION(Value);
    DS_PROPERTY_STORAGE_FIELD(Value);
  private:
    friend class UnitTestClass;
  }a;
  auto res = std::is_same<A::ValueStorageType,PropertyType>::value;
  if(!res){
    FAIL(" the property storage type is incorrect");
  }
  res = std::is_same<A::ValuePropertyType,typename decltype(a._Value)>::value;
  if(!res){
    FAIL(" the field type is incorrect");
  }
};

TTEST_DEFAULT(PropertyPointerStorage, typename PropertyType){
  class A{
    friend class UnitTestClass;
    PropertyType DS_PROPERTY_DEFINITION(Value);
    DS_PROPERTY_STORAGE_POINTER(Value);
  };

  auto res = std::is_pointer<A::ValueStorageType>::value;
  if(!res) FAIL("the property storage type is incorrect (not a pointer");
  res = std::is_same<A::ValueStorageType, std::add_pointer<PropertyType>::type>::value;
  if(!res) FAIL("the type of the storage field is incorrect");
}

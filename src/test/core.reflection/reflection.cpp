#include <core.testing.h>
#include <map>
#include <string>


#define DS_CURRENT_TYPE(CLASSNAME) typedef Person CurrentType;

#define DS_INLINE inline


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

#define DS_PROPERTY_STORAGE(NAME) DS_PROPERTY_STORAGE_NAME(NAME)

#define DS_PROPERTY_GETTER_NAME(NAME) get##NAME
#define DS_PROPERTY_SETTER_NAME(NAME) set##NAME
#define DS_PROPERTY_GETTER_SIGNATURE(NAME) DS_INLINE const DS_PROPERTY_TYPE_NAME(NAME) & DS_PROPERTY_GETTER_NAME(NAME)()const
#define DS_PROPERTY_SETTER_SIGNATURE(NAME) DS_INLINE void DS_PROPERTY_SETTER_NAME(NAME)(const DS_PROPERTY_TYPE_NAME(NAME) & value)
#define DS_PROPERTY_SETTER_SIGNATURE_RVALUE(NAME) DS_INLINE void DS_PROPERTY_SETTER_NAME(NAME)(DS_PROPERTY_TYPE_NAME(NAME) && value)

#define DS_PROPERTY_GETTER(NAME) DS_PROPERTY_GETTER_SIGNATURE(NAME)

#define DS_PROPERTY_SETTER(NAME) DS_PROPERTY_SETTER_SIGNATURE(NAME)

#define DS_PROPERTY_SETTER_RVALUE(NAME) DS_PROPERTY_SETTER_SIGNATURE_RVALUE(NAME)

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


TTEST_DEFAULT(PropertyReferenceStorage, typename PropertyType){
  class A{
    friend class UnitTestClass;
    PropertyType DS_PROPERTY_DEFINITION(Value);
    DS_PROPERTY_STORAGE_REFERENCE(Value);
  };

  auto res = std::is_reference<A::ValueStorageType>::value;
  if(!res) FAIL("the property storage type is incorrect (not a pointer");
  res = std::is_same<A::ValueStorageType, std::add_reference<PropertyType>::type>::value;
  if(!res) FAIL("the type of the storage field is incorrect");
}



TEST(PropertyFieldSetter){
  class A{
    friend class UnitTestClass;
    int DS_PROPERTY_DEFINITION(Value);
    DS_PROPERTY_STORAGE_FIELD(Value);
  public: DS_PROPERTY_SETTER(Value){DS_PROPERTY_STORAGE(Value)=value;}
          

  }a;
  a.setValue(4);
  auto val = a._Value;
  CHECK_EQUAL(4,val);
}
/*
template<typename TValue, typename TStorage>
struct StorageAccess{
  static inline void setStorage(){}
  static inline TValue getStorage(){}
};

  class A{
    int static const * ValueNullPointer(){return 0;} 
    private: typedef std::remove_const<std::remove_pointer<decltype(ValueNullPointer())>::type>::type ValuePropertyType;;
    typedef ValuePropertyType ValueStorageType; ValueStorageType _Value;;
  private: static inline void assign(const ValuePropertyType & value){}
  public: inline void inline void setValue(const ValuePropertyType & value){_Value=value;}
          

  }a;
  */

// int property(Count, storeAs(private: reference), defaultValue(0), public: getter, private: virtual setter, protected: const_reference )
// propertyChanging(Count){}
// propertyValidate(Count){ if (newvalue<0) return false;}
// propertyChanged(Count){}
// 
#include <core.testing.h>
#include <map>
#include <string>

#include <core.property.h>

TEST(1,propertyDefinition){
  struct A{
    std::string DS_PROPERTY_DEFINITION(StringValue)
  private:
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



TTEST_DEFAULT(PropertyField, PropertyType){
  class A{
  public:PropertyType DS_PROPERTY_DEFINITION_TEMPLATED(Value);
  public: DS_PROPERTY_STORAGE_FIELD(Value);
  private:
    friend class UnitTestClass;
  };


  auto res = std::is_same<typename A::ValueStorageType,PropertyType>::value;
  if(!res){
    FAIL(" the property storage type is incorrect");
  }
  typedef decltype(A()._Value) TheType;
  res = std::is_same<typename A::ValueStorageType,TheType>::value;
  if(!res){
    FAIL(" the field type is incorrect");
  }
}


TTEST_DEFAULT(PropertyPointerStorage, PropertyType){
  class A{
    friend class UnitTestClass;
  public:PropertyType DS_PROPERTY_DEFINITION_TEMPLATED(Value);
  public: DS_PROPERTY_STORAGE_POINTER(Value);
  };

  auto res = std::is_pointer<typename A::ValueStorageType>::value;
  if(!res) FAIL("the property storage type is incorrect (not a pointer");
  res = std::is_same< typename A::ValueStorageType,typename std::add_pointer<PropertyType>::type>::value;
  if(!res) FAIL("the type of the storage field is incorrect");
}


TTEST_DEFAULT(PropertyReferenceStorage, PropertyType){
  class A{
    friend class UnitTestClass;
  public:  PropertyType DS_PROPERTY_DEFINITION_TEMPLATED(Value);
  public: DS_PROPERTY_STORAGE_REFERENCE(Value);
  };

  auto res = std::is_reference<typename A::ValueStorageType>::value;
  if(!res) FAIL("the property storage type is incorrect (not a pointer");
  res = std::is_same< typename A::ValueStorageType, PropertyType&>::value;
  if(!res) FAIL("the type of the storage field is incorrect");
}



UNITTEST(PropertyFieldSetter){
  class A{
    friend class UnitTestClass;
    int DS_PROPERTY_DEFINITION(Value);
  public :DS_PROPERTY_STORAGE_FIELD(Value);
  public: DS_PROPERTY_SETTER(Value){DS_PROPERTY_STORAGE(Value)=value;}


  }a;
  a.setValue(4);
  auto val = a._Value;
  CHECK_EQUAL(4,val);
}



UNITTEST(PropertyFieldGetter){
  class A{
    int DS_PROPERTY_DEFINITION(Value);
  public: DS_PROPERTY_STORAGE_FIELD(Value);
  public: DS_PROPERTY_GETTER(Value){return _Value;}
  }a;
  a._Value = 24;
  auto val = a.getValue();
  CHECK_TYPES(decltype(val),int);

  CHECK_EQUAL(24,val);

}


UNITTEST(PropertyFieldAutoSetter){
  class A{
    int DS_PROPERTY_DEFINITION(Value);
  public: DS_PROPERTY_STORAGE_FIELD(Value);
  public: DS_PROPERTY_AUTO_SETTER(Value)
  }a;

  a.setValue(42);
  CHECK_EQUAL(42, a._Value);
}

UNITTEST(PropertyFieldAutoGetter){
  class A{
    int DS_PROPERTY_DEFINITION(Value);
  public: DS_PROPERTY_STORAGE_FIELD(Value);
  public: DS_PROPERTY_AUTO_GETTER(Value)
  }a;

  a._Value = 312;
  CHECK_EQUAL(312,a.getValue());

}


UNITTEST(PropertyFieldVirtualSetter){
  class A{
    int DS_PROPERTY_DEFINITION(Value);
  public: DS_PROPERTY_STORAGE_FIELD(Value);
  public: virtual DS_PROPERTY_AUTO_SETTER(Value)

  };

  class B : public A{
  public: DS_PROPERTY_SETTER(Value){
            A::setValue(value+1);
          }
  }b;
  b.setValue(44);

  CHECK_EQUAL(45,b._Value);

}
UNITTEST(PropertyFieldVirtualGetter){
  class A{
    int DS_PROPERTY_DEFINITION(Value);
  public: DS_PROPERTY_STORAGE_FIELD(Value);
  public: virtual DS_PROPERTY_AUTO_GETTER(Value)

  };

  class B : public A{
  public: 
    DS_PROPERTY_GETTER(Value){
      return A::getValue()+1;
    }
  }b;
  b._Value= 2;
  CHECK_EQUAL(3,b.getValue());
}



//#define property



/*
#define DS_PROPERTY_CALLBACK_GETTER(NAME,callback)
template<typename T>
struct ArgumentType{

};
template<typename R, typename A1>
struct ArgumentType<R (*)(A1)>{
typedef A1 type;
};
template<typename C,typename R, typename A1>
struct ArgumentType<R (C::*)(A1)>{
typedef A1 type;
};


UNITTEST(ArgumentTypeMemberFunction){
struct A{
void testmethod(double arg){};
}a;
ArgumentType<&A::testmethod>::type;
}
UNITTEST(ArgumentTypeStaticFunction){
struct A{
static void testmethod(float arg){};
};
ArgumentType<&A::testmethod>::type;
}
*/
/*
UNITTEST(PropertyCallbackGetter){
class A{
int DS_PROPERTY_DEFINITION(Value);
public: DS_PROPERTY_STORAGE_FIELD(Value);
public: auto getValue()->decltype(getCallback()){return getCallback();}
void setValue(const ValuePropertyType & value){setCallback(value);}

}a;
}
*/




UNITTEST(ExtensiblePropertyDefintion){

  struct ExtendedPropertyTestStruct{
    DS_PROPERTY_EXTENSION_METHODS;

    ExtendedPropertyTestStruct():_RedChannel(0),beforeSetCallCount(0),afterSetCallCount(0),beforeGetCallCount(0),cancelSetResult(false){}

    // counters for accessing callcount
    int beforeSetCallCount;
    int afterSetCallCount;
    mutable int beforeGetCallCount;
    bool cancelSetResult;


    // define a default extended property - a property which has extension points for setting and getting
    float DS_PROPERTY_EXTENDED(RedChannel);


    before_set(RedChannel){
      beforeSetCallCount++;
      return cancelSetResult;
    }

    after_set(RedChannel){
      afterSetCallCount++;
    }


    before_get(RedChannel){
      beforeGetCallCount++;
    }

  };
  ExtendedPropertyTestStruct uut;
  CHECK_EQUAL(0,uut.afterSetCallCount);
  CHECK_EQUAL(0,uut.beforeGetCallCount);
  CHECK_EQUAL(0,uut.beforeSetCallCount);

  uut.setRedChannel(42);  

  CHECK_EQUAL(42,uut.getRedChannel());
  CHECK_EQUAL(1,uut.beforeGetCallCount);

  uut.setRedChannel(41);

  uut.cancelSetResult = true;
  uut.setRedChannel(1);

  auto val = uut.getRedChannel();

  CHECK_EQUAL(41,val);
  CHECK_EQUAL(2,uut.beforeGetCallCount);
  CHECK_EQUAL(2,uut.afterSetCallCount);
  CHECK_EQUAL(3,uut.beforeSetCallCount);

}

/*
template<typename T1, typename T2>
struct TemplatedExtensiblePropertyTestUnit{
DS_PROPERTY_EXTENSION_METHODS;

std::stringstream result;

T1 DS_PROPERTY_EXTENDED_TEMPLATED(Value1);

beforeGet(Value1){
result<<"getValue1";
}

afterSet(Value1){
result<<"afterSetValue1";
result<<"afterSetValue1"<<_Value1;
}
beforeGet(Value1){
result << "beforeGetValue1";
}

T2 DS_PROPERTY_EXTENDED(Value2);

beforeGet(Value2){
result<<"getValue2";
}

afterSet(Value2){
result<<"afterSetValue2";
result<<"afterSetValue2"<<_Value2;
}
beforeGet(Value2){
result << "beforeGetValue2";
}


};
UNITTEST(TemplatedExtendedProperty){
TemplatedExtensiblePropertyTestUnit<std::string,int> uut;
uut.setValue1("hello");
uut.setValue2(31);

auto a = uut.getValue1();
auto b = uut.getValue2();

auto str = uut.result.str();
}*/
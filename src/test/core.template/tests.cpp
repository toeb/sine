#include <core.testing.h>
#include <map>
#include <string>


UNITTEST(DS_REDUCE){
#define my_op +
  int i = DS_REDUCE(,my_op,1,1,1,1,1,1);
  CHECK_EQUAL(6,i);
#undef my_op
}


UNITTEST(DS_REDUCE_N){
#define my_op +
  int i = DS_REDUCE_N(5,,my_op,1,1,1,1,1);
  CHECK_EQUAL(5,i);
#undef my_op
}

UNITTEST(DS_REDUCE_3){
#define my_op +
  int i = DS_REDUCE_3(,my_op,2,3,4);
  CHECK_EQUAL(9,i);
#undef my_op
}

UNITTEST(DS_REDUCE_2){
#define my_op +
  int i = DS_REDUCE_2(,my_op,2,3);
  CHECK_EQUAL(5,i);
#undef my_op
}

UNITTEST(DS_REDUCE_1){
#define my_op +
  int i = DS_REDUCE_1(,my_op,2);
  CHECK_EQUAL(2,i);
#undef my_op
}

UNITTEST(DS_NUM_ARGS1){
  int i= DS_NUM_ARGS(a ,b, c, 3, 4, 5,1, 2, asdasd);
  CHECK_EQUAL(9,i);
}

UNITTEST(DS_NUM_ARGS2){
  int i = DS_NUM_ARGS();
  //todo.  implement DS_NUM_ARGS to work for 0
  //CHECK_EQUAL(0,i);

}


UNITTEST(DS_FOREACH){
  int x=0;
#define MY_OP(X) x++;
  DS_FOREACH(MY_OP,x,x,x,x,x,x,x,x,x);
  CHECK_EQUAL(9,x);

#undef MY_OP

}

UNITTEST(DS_FOREACH_N){
  int x=0;
#define MY_OP(X) x++;
  DS_FOREACH_N(7,MY_OP,x,x,x,x,x,x,x);
  CHECK_EQUAL(7,x);

#undef MY_OP

}

UNITTEST(DS_FOREACH_10) {
  int x=0;
#define MY_OP(X) x++;
  DS_FOREACH_10(MY_OP,x,x,x,x,x,x,x,x,x,x);
  CHECK_EQUAL(10,x);

#undef MY_OP
}

UNITTEST(DS_FOREACH_1){
  int x=2;

#define MY_OP(X) X=X*X;
  DS_FOREACH_1(MY_OP,x)

    CHECK_EQUAL(x,4);
#undef MY_OP
}

UNITTEST(DS_FOREACH_2){
  int x=2;
  int y=3;
#define MY_OP(X) X=X*X;
  DS_FOREACH_2(MY_OP,x,y);

  CHECK_EQUAL(x,4);
  CHECK_EQUAL(y,9);
#undef MY_OP
}

UNITTEST(DS_FOREACH_3){
  int x=2;
#define MY_OP(X) X=X*X;
  DS_FOREACH_3(MY_OP,x,x,x);

  CHECK_EQUAL(x,256);
#undef MY_OP
}
UNITTEST(DS_FIRST){
  int i=0;
  int j=0;
  int k=0;

  DS_FIRST(i++;,j++;,k++;);
  CHECK_EQUAL(1,i);
  CHECK_EQUAL(0,j);
  CHECK_EQUAL(0,k);

}

UNITTEST(DS_STRINGIFY){
  const char * cstr= DS_STRINGIFY(int);
  CHECK_EQUAL(std::string("int"),std::string(cstr));

}

UNITTEST(DS_REST){
  int ar[3] = {DS_REST(1,2,3,4)};

  CHECK_EQUAL(ar[0],2);
  CHECK_EQUAL(ar[1],3);
  CHECK_EQUAL(ar[2],4);
}

#define DS_CURRENT_TYPE(CLASSNAME) typedef Person CurrentType;

#define DS_INLINE inline


#define DS_PROPERTY_NAME(NAME) NAME

#define DS_PROPERTY_TYPE_NAME(NAME) DS_CONCAT(DS_PROPERTY_NAME(NAME),PropertyType)

#define DS_STATIC_TYPE_DEFINITION_HELPER_NAME(NAME) DS_CONCAT(DS_PROPERTY_NAME(NAME),NullPointer)
// the typedef is protected because subclasses might need access
#define DS_PROPERTY_TYPE_DEFINITION(NAME) protected: typedef nspace::result_of_static_function< decltype( &DS_STATIC_TYPE_DEFINITION_HELPER_NAME(NAME) ) >::type DS_PROPERTY_TYPE_NAME(NAME); //this is the definition of the property type
#define DS_PROPERTY_TYPE_DEFINITION_TEMPLATED(NAME) private: typedef typename  nspace::result_of_static_function< decltype( &DS_STATIC_TYPE_DEFINITION_HELPER_NAME(NAME) ) >::type DS_PROPERTY_TYPE_NAME(NAME);

#define DS_PROPERTY_DEFINITION(NAME) /* Begginning of Property */\
  static DS_STATIC_TYPE_DEFINITION_HELPER_NAME(NAME)();/*this should not create any overhead and is possible for any type*/\
  DS_PROPERTY_TYPE_DEFINITION(NAME) /* Define Property type */


#define DS_PROPERTY_DEFINITION_TEMPLATED(NAME) \
  static DS_STATIC_TYPE_DEFINITION_HELPER_NAME(NAME)();/*this should not create any overhead and is possible for any type*/\
  DS_PROPERTY_TYPE_DEFINITION_TEMPLATED(NAME) /* Define Property type */

// there can be field storage pointer storage, refence storage and callback storage
// 

#define DS_PROPERTY_STORAGE_NAME(NAME) DS_CONCAT(_, DS_PROPERTY_NAME(NAME))

#define DS_PROPERTY_STORAGE_TYPE_NAME(NAME) DS_CONCAT(DS_PROPERTY_NAME(NAME),StorageType)

#define DS_PROPERTY_STORAGE_TYPE_FIELD(NAME) typedef DS_PROPERTY_TYPE_NAME(NAME) DS_PROPERTY_STORAGE_TYPE_NAME(NAME);
#define DS_PROPERTY_STORAGE_TYPE_POINTER(NAME) typedef DS_PROPERTY_TYPE_NAME(NAME) * DS_PROPERTY_STORAGE_TYPE_NAME(NAME);
#define DS_PROPERTY_STORAGE_TYPE_REFERENCE(NAME) typedef DS_PROPERTY_TYPE_NAME(NAME) & DS_PROPERTY_STORAGE_TYPE_NAME(NAME);

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




#define DS_PROPERTY_AUTO_SETTER(NAME) DS_PROPERTY_SETTER(NAME){ DS_PROPERTY_STORAGE(NAME) = value; } DS_PROPERTY_SETTER_RVALUE(NAME){ DS_PROPERTY_STORAGE(NAME) = value;}
#define DS_PROPERTY_AUTO_GETTER(NAME) DS_PROPERTY_GETTER(NAME){ return DS_PROPERTY_STORAGE(NAME); }


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
  }a;


  auto res = std::is_same<typename A::ValueStorageType,PropertyType>::value;
  if(!res){
    FAIL(" the property storage type is incorrect");
  }
  typedef  decltype(a._Value) TheType;
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



#define DS_CHECK_TYPES(...)\
{if(!std::is_same<DS_REDUCE_COMMA(DS_NOOP, __VA_ARGS__)>::value)FAIL("The following types are not the equal: '<" << #__VA_ARGS__<<"'>");}

#ifndef CHECK_TYPES
#define CHECK_TYPES(...) DS_CHECK_TYPES(__VA_ARGS__)
#endif

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
  public: DS_PROPERTY_GETTER(Value){
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
/*  It is relatively ugly but one could use define to set the propertyname
#define DS_PROPERTY_NAME Value
DEFINITION;
private: FIELD_STORAGE;
protected: virtual SETTER;
public: GETTER;


#undef DS_PROPERTY_NAME


*/




// this occurs when only name is given
#define DS_PROPERTY_0(NAME) 


#define DS_APPLY_NAME(X) X(NAME)

#define DS_PROPERTY_1(NAME,...) 
#define DS_PROPERTY_2(NAME,...) 

#define DS_PROPERTY_3(NAME,...) 
#define DS_PROPERTY_4(NAME,...) 
#define DS_PROPERTY_5(NAME,...) 


#define DS_PROPERTY_N(NAME,N,...) DS_CONCAT(DS_PROPERTY_,N)(__VA_ARGS__)


#define basic_property(NAME) \
  DS_PROPERTY_DEFINITION(NAME)\
  private: DS_PROPERTY_STORAGE_FIELD(NAME);  public: DS_PROPERTY_AUTO_GETTER(NAME); public:DS_PROPERTY_AUTO_SETTER(NAME)



#define DS_PROPERTY_EXTENSIBLE_SET(NAME)


#define DS_PROPERTY_SETTER_BEFORE_NAME(NAME) DS_CONCAT(DS_CONCAT(onBefore,NAME),Set)
#define DS_PROPERTY_SETTER_AFTER_NAME(NAME) DS_CONCAT(DS_CONCAT(onAfter,NAME),Set)
#define DS_PROPERTY_SETTER_BEFORE_SIGNATURE(NAME) void DS_INLINE DS_PROPERTY_SETTER_BEFORE_NAME(NAME)(const DS_PROPERTY_TYPE_NAME(NAME) & newvalue, bool & cancel)
#define DS_PROPERTY_SETTER_AFTER_SIGNATURE(NAME) void DS_INLINE DS_PROPERTY_SETTER_AFTER_NAME(NAME)()

#define beforeSet(NAME) DS_PROPERTY_SETTER_BEFORE_SIGNATURE(NAME)
#define afterSet(NAME) DS_PROPERTY_SETTER_AFTER_SIGNATURE(NAME)
#define cancelSet() { cancel = true; return;}


#define validating_property(NAME) \
  DS_PROPERTY_DEFINITION(NAME)\
  private: DS_PROPERTY_STORAGE_FIELD(NAME);  public: DS_PROPERTY_AUTO_GETTER(NAME); public DS_PROPERTY_SETTER(NAME){bool cancel=false; DS_PROPERTY_SETTER_BEFORE_NAME(NAME)(value,cancel); if(cancel)return; DS_PROPERTY_STORAGE(NAME)=value; } private: DS_PROPERTY_SETTER_BEFORE_SIGNATURE(NAME)


/*

template<typename T>
struct hasBeforeSetMethod{
static const bool value = false;
};

template<typename T>
struct hasBeforeSetMethod<typename T::BeforeSetValue>{
static const bool value = true;
};
*/
struct FalseType{
  static const bool value=false;
};
struct TrueType{

  static const bool value=true;
};




/*
#define DS_HAS_MEMBER_CHECK(MEMBERNAME)
template<typename T> struct has_member_check_##MEMBERNAME { 
struct Fallback { int MEMBERNAME; }; // introduce member name "x"
struct Derived : T, Fallback { };

template<typename C, C> struct ChT; 

template<typename C> static char (&f(ChT<int Fallback::*, &C::MEMBERNAME>*))[1]; 
template<typename C> static char (&f(...))[2]; 

static bool const value = sizeof(f<Derived>(0)) == 2;
}; 


#define DS_HAS_MEMBER(NAME) 
struct A { int x; };

struct B { int X; };*/

#define DS_MINIMAL_GET(NAME) DS_PROPERTY_GETTER(NAME){ return DS_PROPERTY_STORAGE(NAME);  }
#define DS_MINIMAL_SET(NAME) DS_PROPERTY_SETTER(NAME){ DS_PROPERTY_STORAGE(NAME) = value; }

#define DS_CURRENT_CLASS(CLASSNAME) typedef CLASSNAME CurrentClassType;


#define DS_PROPERTY_MARKER(NAME) DS_CONCAT(NAME,PropertyMarker)
#define DS_PROPERTY_MARKER_DEFINITION(NAME) struct DS_PROPERTY_MARKER(NAME){ };

/*  This works with MSVC however specialization of template methods inside of a class is not part of the C++ standard --> GCC fails
    Also a limitation (albeit a negligable one) is that you may not use this as a  local struct because of templating
#define DS_PROPERTY_EXTENSION_BEFORE_SET_NAME onBeforePropertySet
#define DS_PROPERTY_EXTENSION_AFTER_SET_NAME onAfterPropertySet
#define DS_PROPERTY_EXTENSION_BEFORE_GET_NAME onBeforePropertyGet

#define DS_PROPERTY_EXTENSION_BEFORE_SET  template<typename MarkerType,typename ValueType> DS_INLINE bool DS_PROPERTY_EXTENSION_BEFORE_SET_NAME(const ValueType & value){return false;}
#define DS_PROPERTY_EXTENSION_AFTER_SET   template<typename MarkerType> DS_INLINE void DS_PROPERTY_EXTENSION_AFTER_SET_NAME(){}
#define DS_PROPERTY_EXTENSION_BEFORE_GET  template<typename MarkerType> DS_INLINE void DS_PROPERTY_EXTENSION_BEFORE_GET_NAME()const{}

#define DS_PROPERTY_EXTENSION_BEFORE_SET_IMPLEMENTATION(NAME) template<> DS_INLINE bool DS_PROPERTY_EXTENSION_BEFORE_SET_NAME<DS_PROPERTY_MARKER(NAME),  DS_PROPERTY_TYPE_NAME(NAME)>(const DS_PROPERTY_TYPE_NAME(NAME) & newvalue)
#define DS_PROPERTY_EXTENSION_AFTER_SET_IMPLEMENTATION(NAME)  template<> DS_INLINE void DS_PROPERTY_EXTENSION_AFTER_SET_NAME< DS_PROPERTY_MARKER(NAME)>()
#define DS_PROPERTY_EXTENSION_BEFORE_GET_IMPLEMENTATION(NAME) template<> DS_INLINE void DS_PROPERTY_EXTENSION_BEFORE_GET_NAME< DS_PROPERTY_MARKER(NAME)>()const


#define DS_PROPERTY_EXTENSION_METHODS\
  DS_PROPERTY_EXTENSION_BEFORE_SET\
  DS_PROPERTY_EXTENSION_AFTER_SET\
  DS_PROPERTY_EXTENSION_BEFORE_GET\

#define DS_PROPERTY_BEFORE_SET(NAME) DS_PROPERTY_EXTENSION_BEFORE_SET_IMPLEMENTATION(NAME) //DS_INLINE bool before##NAME##Set(const DS_PROPERTY_TYPE_NAME(NAME) & value)
#define DS_PROPERTY_AFTER_SET(NAME) DS_PROPERTY_EXTENSION_AFTER_SET_IMPLEMENTATION(NAME)//DS_INLINE void after##NAME##Set()
#define DS_PROPERTY_BEFORE_GET(NAME) DS_PROPERTY_EXTENSION_BEFORE_GET_IMPLEMENTATION(NAME)//DS_INLINE void before##NAME##Get()const

#define beforeSet(NAME) DS_PROPERTY_BEFORE_SET(NAME)
#define afterSet(NAME) DS_PROPERTY_AFTER_SET(NAME)
#define beforeGet(NAME) DS_PROPERTY_BEFORE_GET(NAME)

#define DS_PROPERTY_SETTER_EXTENDED(NAME) DS_PROPERTY_SETTER(NAME){ if( DS_PROPERTY_EXTENSION_BEFORE_SET_NAME<DS_PROPERTY_MARKER(NAME),DS_PROPERTY_TYPE_NAME(NAME)>(value))return; DS_PROPERTY_STORAGE(NAME) = value; DS_PROPERTY_EXTENSION_AFTER_SET_NAME<DS_PROPERTY_MARKER(NAME)>();}
#define DS_PROPERTY_GETTER_EXTENDED(NAME) DS_PROPERTY_GETTER(NAME){ DS_PROPERTY_EXTENSION_BEFORE_GET_NAME<DS_PROPERTY_MARKER(NAME)>(); return DS_PROPERTY_STORAGE(NAME); }
        

#define DS_PROPERTY_EXTENDED(NAME)\
  DS_PROPERTY_DEFINITION(NAME)\
  DS_PROPERTY_MARKER_DEFINITION(NAME)\
  DS_PROPERTY_STORAGE_FIELD(NAME)\
  public: DS_PROPERTY_GETTER_EXTENDED(NAME)\
  public: DS_PROPERTY_SETTER_EXTENDED(NAME)
  */
// This is plattform indepenedent.  it uses overloading and a markertypes to call default/custom extension methods
// it works for classes and structs in namespaces, classes as well as methods
// furthermore you must not define the general (empty implementations) of the extension methods in the class if every property defines all extensions
// I strongly believe( have not checked) that there is no overhead when the compiler is done optimizing code.  I may be mistaken
// these do not work with templated arguments you must use the correct
#define DS_PROPERTY_EXTENSION_BEFORE_SET_NAME onBeforePropertySet
#define DS_PROPERTY_EXTENSION_AFTER_SET_NAME onAfterPropertySet
#define DS_PROPERTY_EXTENSION_BEFORE_GET_NAME onBeforePropertyGet

#define DS_PROPERTY_EXTENSION_BEFORE_SET  DS_INLINE bool DS_PROPERTY_EXTENSION_BEFORE_SET_NAME(const void * marker, const void * value){return false;}
#define DS_PROPERTY_EXTENSION_AFTER_SET   DS_INLINE void DS_PROPERTY_EXTENSION_AFTER_SET_NAME(const void * marker){}
#define DS_PROPERTY_EXTENSION_BEFORE_GET  DS_INLINE void DS_PROPERTY_EXTENSION_BEFORE_GET_NAME(const void * marker)const{}

#define DS_PROPERTY_EXTENSION_BEFORE_SET_IMPLEMENTATION(NAME) DS_INLINE bool DS_PROPERTY_EXTENSION_BEFORE_SET_NAME(const DS_PROPERTY_MARKER(NAME)*,  const DS_PROPERTY_TYPE_NAME(NAME) * newvalue)
#define DS_PROPERTY_EXTENSION_AFTER_SET_IMPLEMENTATION(NAME)  DS_INLINE void DS_PROPERTY_EXTENSION_AFTER_SET_NAME(const DS_PROPERTY_MARKER(NAME)*)
#define DS_PROPERTY_EXTENSION_BEFORE_GET_IMPLEMENTATION(NAME) DS_INLINE void DS_PROPERTY_EXTENSION_BEFORE_GET_NAME(const DS_PROPERTY_MARKER(NAME)*)const


#define DS_PROPERTY_EXTENSION_METHODS\
  DS_PROPERTY_EXTENSION_BEFORE_SET   \
  DS_PROPERTY_EXTENSION_AFTER_SET    \
  DS_PROPERTY_EXTENSION_BEFORE_GET   \

#define DS_PROPERTY_BEFORE_SET(NAME) DS_PROPERTY_EXTENSION_BEFORE_SET_IMPLEMENTATION(NAME) //DS_INLINE bool before##NAME##Set(const DS_PROPERTY_TYPE_NAME(NAME) & value)
#define DS_PROPERTY_AFTER_SET(NAME) DS_PROPERTY_EXTENSION_AFTER_SET_IMPLEMENTATION(NAME)//DS_INLINE void after##NAME##Set()
#define DS_PROPERTY_BEFORE_GET(NAME) DS_PROPERTY_EXTENSION_BEFORE_GET_IMPLEMENTATION(NAME)//DS_INLINE void before##NAME##Get()const

#define beforeSet(NAME) DS_PROPERTY_BEFORE_SET(NAME)
#define afterSet(NAME) DS_PROPERTY_AFTER_SET(NAME)
#define beforeGet(NAME) DS_PROPERTY_BEFORE_GET(NAME)
#define DS_PROPERTY_MARKER_INSTANCE(NAME) static_cast<const DS_PROPERTY_MARKER(NAME)*>(0)
#define DS_PROPERTY_SETTER_EXTENDED(NAME) DS_PROPERTY_SETTER(NAME){ if(DS_PROPERTY_EXTENSION_BEFORE_SET_NAME(DS_PROPERTY_MARKER_INSTANCE(NAME), &value))return; DS_PROPERTY_STORAGE(NAME) = value; DS_PROPERTY_EXTENSION_AFTER_SET_NAME(DS_PROPERTY_MARKER_INSTANCE(NAME));}
#define DS_PROPERTY_GETTER_EXTENDED(NAME) DS_PROPERTY_GETTER(NAME){ DS_PROPERTY_EXTENSION_BEFORE_GET_NAME(DS_PROPERTY_MARKER_INSTANCE(NAME)); return DS_PROPERTY_STORAGE(NAME); }
        

#define DS_PROPERTY_EXTENDED(NAME)\
  DS_PROPERTY_DEFINITION(NAME)\
  DS_PROPERTY_MARKER_DEFINITION(NAME)\
  DS_PROPERTY_STORAGE_FIELD(NAME)\
  public: DS_PROPERTY_GETTER_EXTENDED(NAME)\
  public: DS_PROPERTY_SETTER_EXTENDED(NAME)

// todo:
/*
#define DS_PROPERTY_EXTENDED_TEMPLATED(NAME)\
  DS_PROPERTY_DEFINITION_TEMPLATED(NAME)    \
  DS_PROPERTY_MARKER_DEFINITION(NAME)       \
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

  
  beforeSet(RedChannel){
    beforeSetCallCount++;
    return cancelSetResult;
  }

  afterSet(RedChannel){
    afterSetCallCount++;
  }


  beforeGet(RedChannel){
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
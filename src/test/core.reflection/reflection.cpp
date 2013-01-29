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

    template<typename T>  static auto IsSomeMethodDefined(T & t)->typename decltype(t.someMethod(),FalseType);
 struct AF{
    int basic_property(Value0)
    int basic_property(Value1)
    //int validating_property(Value2)

   // int property(Value2, field,private_get,
 

  };

UNITTEST(SimplifiedPropertyDefintion){




}
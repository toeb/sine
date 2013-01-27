#include <core.testing.h>
#include <map>
#include <string>

TTEST(Ttesttest, T,K){
  bool res = std::is_same<T,K>::value;
  CHECK(res);
}

TTEST_INSTANCE(Ttesttest,int,int);
TTEST_INSTANCE(Ttesttest,int,double);
TTEST_INSTANCE(Ttesttest,int,std::string);
TTEST_INSTANCE(Ttesttest,std::string,std::string);



UNITTEST(DS_REDUCE){
#define my_op +
  int i = DS_REDUCE(,my_op,1,1,1,1,1,1);
  CHECK_EQUAL(6,i);
#undef my_op;
}


UNITTEST(DS_REDUCE_N){
#define my_op +
  int i = DS_REDUCE_N(5,,my_op,1,1,1,1,1);
  CHECK_EQUAL(5,i);
#undef my_op;
}

UNITTEST(DS_REDUCE_3){
#define my_op +
  int i = DS_REDUCE_3(,my_op,2,3,4);
  CHECK_EQUAL(9,i);
#undef my_op;
}

UNITTEST(DS_REDUCE_2){
#define my_op +
  int i = DS_REDUCE_2(,my_op,2,3);
  CHECK_EQUAL(5,i);
#undef my_op;
}

UNITTEST(DS_REDUCE_1){
#define my_op +
  int i = DS_REDUCE_1(,my_op,2);
  CHECK_EQUAL(2,i);
#undef my_op;
}

UNITTEST(DS_NUM_ARGS1){
  int i= DS_NUM_ARGS(a ,b, c, 3, 4, 5,1, 2, asdasd);
  CHECK_EQUAL(9,i);
}

UNITTEST(DS_NUM_ARGS2){
  int i = DS_NUM_ARGS();
  CHECK_EQUAL(0,i);
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

#define DS_PROPERTY_TYPE_DEFINITION(NAME) private: typedef std::remove_const<std::remove_pointer<decltype(DS_STATIC_TYPE_DEFINITION_HELPER_NAME(NAME)())>::type>::type DS_PROPERTY_TYPE_NAME(NAME); //this is the definition of the property type

#define DS_PROPERTY_DEFINITION(NAME) /* Begginning of Property */\
  static const * DS_STATIC_TYPE_DEFINITION_HELPER_NAME(NAME)(){return 0;}/*this should not create any overhead and is possible for any type*/\
  DS_PROPERTY_TYPE_DEFINITION(NAME) /* Define Property type */

// there can be field storage pointer storage, refence storage and callback storage
// 

#define DS_PROPERTY_STORAGE_NAME(NAME) DS_CONCAT(_, DS_PROPERTY_NAME(NAME))

#define DS_PROPERTY_STORAGE_TYPE_NAME(NAME) DS_CONCAT(DS_PROPERTY_NAME(NAME),StorageType)

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


template<typename T>
struct ClassA{
  void test();
};

template<typename T>
void ClassA< T>::test(){
  std::cout << "lol";
}


UNITTEST(typenameTest){
  ClassA<int>  asd;
  asd.test();
}

/*

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

*/

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
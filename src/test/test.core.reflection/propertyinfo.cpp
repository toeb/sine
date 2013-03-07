#include <core.testing.h>
#include <core.reflection.h>
#include <memory>
using namespace nspace;

namespace n2{
  struct PropertyInfo : public MemberInfo{
    typedef const MethodInfo * basic_property(GetMethod);
    typedef const MethodInfo * basic_property(SetMethod);
    typedef const Type * basic_property(PropertyType);
  protected:
    PropertyInfo(const std::string & name, const MethodInfo * getter, const MethodInfo * setter):MemberInfo(name),_SetMethod(setter),_GetMethod(getter){
      const Type *  propertyType=0;
      if(getter){
        if(getter->getArgumentTypes().size()!=0){
          std::cerr << "getter is not a parameterless method. ignoring"<<std::endl;
          _GetMethod=0;
        }else{
          auto type = getter->getReturnType()->removeConst()->removeReference();
          propertyType = type->removeConst()->removeReference();
        }
      }
      if(setter){
        if(setter->getArgumentTypes().size()!=1){
          std::cerr<<"setter method is not a single parameter method"<<std::endl;          
        }else{
          auto type = setter->getArgumentTypes().at(0)->removeReference()->removeConst();
          if(propertyType){
            if(propertyType!=type){
              std::cerr<<"getter and setter raw types do not match"<<std::endl;

            }else{
              // find closest relation 
              
            }
          }else{
            propertyType = type;
          }
          
        }
      }
    }
  public:
    
    bool isGettable()const{return getGetMethod()!=0;}
    bool isSettable()const{return getSetMethod()!=0;}

    Argument get(const void * ptr)const{
      if(!isGettable())return Argument();
      auto getter = getGetMethod();
      return getter->call(ptr);
    }
    Argument get(void * ptr)const{
      if(!isGettable())return Argument();
      auto getter = getGetMethod();
      return getter->call(ptr);
    }
    void set(void * ptr, Argument argument)const{
      if(!isSettable())return;
      auto setter = getSetMethod();
      Argument args[1]={argument};
      setter->call(ptr,args);

    }
    void set(const void * ptr , Argument argument)const{ 
      if(!isSettable())return;
      auto setter = getSetMethod();
      Argument args[1]={argument};
      setter->call(ptr,args);
    }
  };

  template<typename ClassType>
  struct TypedPropertyInfo:public PropertyInfo{
    TypedPropertyInfo(const std::string & name, const MethodInfo * getter, const MethodInfo * setter):PropertyInfo(name,getter,setter){
      setPropertyType(typeof(ClassType));
    }
  };

#define DS_REFLECT_PROPERTY(NAME, GETTER, SETTER)\
  DS_INITIALIZER_STATIC(NAME##Property){\
  auto type = const_cast<Type*>(typeof(CurrentClassType));\
  auto getter = type->getMethod(#GETTER);\
  auto setter = type->getMethod(#SETTER);\
  auto info = new TypedPropertyInfo<CurrentClassType>(#NAME,getter,setter);\
  type->Members()|=info;\
  }
  
#define DS_REFLECT_PROPERTY_DEFINITION(...) DS_EXPAND(DS_CONCAT(DS_REFLECT_PROPERTY_DEFINITION_,DS_NUM_ARGS(__VA_ARGS__))(__VA_ARGS__))
  
#define DS_REFLECT_PROPERTY_DEFINITION_3(NAME,GETTER,SETTER) \
  DS_REFLECTION_METHOD(GETTER);\
  DS_REFLECTION_METHOD(SETTER);\
  DS_REFLECT_PROPERTY(NAME,GETTER,SETTER)

#define DS_REFLECT_PROPERTY_DEFINITION_2(NAME,PROPERTY_DEFINITION) PROPERTY_DEFINITION(NAME); \
  DS_REFLECT_PROPERTY_DEFINITION_3(NAME,DS_PROPERTY_GETTER_NAME(NAME),DS_PROPERTY_SETTER_NAME(NAME))

#define DS_REFLECT_PROPERTY_DEFINITION_1(NAME) DS_REFLECT_PROPERTY_DEFINITION_2(NAME, DS_PROPERTY_BASIC)

#define reflect_property(...)  DS_REFLECT_PROPERTY_DEFINITION(__VA_ARGS__) 
#define reflect_method_property(GETTER,SETTER) DS_REFLECT_PROPERTY_DEFINITION_3(GETTER,GETTER,SETTER)


TEST(1, propertyTest){
  struct A{
    reflect_type(A);
    int prop()const{return 1;}
    void setProp(const int i){};


    reflect_property(Prop,prop,setProp)

    //reflect_property(prop, setProp);
  };

  A a;
  auto type = typeof(A);
  auto prop = dynamic_cast<const PropertyInfo*>(type->getMember("Prop"));
 auto result = (int)prop->get(&a);
 CHECK(result==1);
}
namespace testNamespace{
  struct A{
    reflect_type(A);
  public:
    typedef int reflect_property(TestProperty);

  public:
    typedef int * reflect_property(TestPropertyTwo);
  public:
    typedef std::shared_ptr<double> reflect_property(TestPropertyThree);

    
  public:
    A():_TestProperty(3),_TestPropertyTwo(new int(3232)){}
  };

TEST(Gettable,PropertyInfo){
  A a;
  auto property = (const n2::PropertyInfo*)typeof(A)->getMember("TestProperty");  
  CHECK(property->isGettable());  
}

TEST(Settable,PropertyInfo){
  A a;
  auto property = (const n2::PropertyInfo*)typeof(A)->getMember("TestProperty");
  CHECK(property->isSettable());
}
TEST(GetValue,PropertyInfo){
  A a;
  auto prop = (const n2::PropertyInfo*)typeof(A)->getMember("TestProperty");
  CHECK_EQUAL(3,(int)prop->get(&a));
}

TEST(SetValue, PropertyInfo){
  A a;
  auto prop = (const n2::PropertyInfo*)typeof(A)->getMember("TestProperty");
  prop->set(&a,88);
  CHECK(88, a.getTestProperty());
}


TEST(GetPointerValue,PropertyInfo){
  A a;
  auto prop = (const n2::PropertyInfo*)typeof(A)->getMember("TestPropertyTwo");
  auto val = (int*)prop->get(&a);
  CHECK_EQUAL(3232,*val);
}

TEST(GetSmartPointer,PropertyInfo){
  A a;
  std::shared_ptr<double> thePointer(new double(141));
  a.setTestPropertyThree(thePointer);
  
  auto prop = (const n2::PropertyInfo*)typeof(A)->getMember("TestPropertyThree");  
  auto val = (std::shared_ptr<double>) prop->get(&a);
  CHECK(141,*val);
}


}
}


#include <core.testing.h>
#include <core.reflection.h>
using namespace nspace;

namespace n2{
  struct PropertyInfo : public MemberInfo{
    typedef const MethodInfo * basic_property(GetMethod);
    typedef const MethodInfo * basic_property(SetMethod);
    typedef const Type * basic_property(PropertyType);
  public:
    Argument get(const void * ptr)const{
      auto getter = getSetMethod();
      return getter->call(ptr);
    }
    Argument get(void * ptr)const{
      auto getter = getSetMethod();
      return getter->call(ptr);

    }
    void set(void * ptr, Argument argument)const{
      auto setter = getSetMethod();
      Argument args[1]={argument};
      setter->call(ptr,args);

    }
    void set(const void * ptr , Argument argument)const{ 
      auto setter = getSetMethod();
      Argument args[1]={argument};
      setter->call(ptr,args);
    }
  };

  template<typename ClassType>
  struct TypedPropertyInfo:public PropertyInfo{
    TypedPropertyInfo(){
      setPropertyType(typeof(ClassType));

    }
  };

#define reflect_property(NAME, GETTER, SETTER) DS_REFLECTION_METHOD(GETTER); DS_REFLECTION_METHOD(SETTER);\
  DS_ONCE{\
  static TypedPropertyInfo<CurrentClassType> propertyInfo();\
  \
  }
TEST(1, propertyTest){
  struct A{
    reflect_type(A);
    int prop()const{return 1;}
    void setProp(const int i){};

    reflect_method(prop);
    reflect_method(setProp);
   DS_ONCE{
     static TypedPropertyInfo<CurrentClassType> info;
     auto type = const_cast<Type*>(typeof(CurrentClassType));
     info.setName("Prop");
     info.setGetMethod(type->getMethod("prop"));
     info.setSetMethod(type->getMethod("setProp"));
     type->Members() |= &info;

   }
    //reflect_property(prop, setProp);
  };

  A a;
  auto type = typeof(A);
  auto prop = dynamic_cast<const PropertyInfo*>(type->getMember("Prop"));
  auto result = (int)prop->get(&a);
  CHECK(result==1);
}



}
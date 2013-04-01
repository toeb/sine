#pragma once 
#include <core.reflection/type/TypeInfo.h>

#include <core.reflection/member/method/TypedMethodInfo.h>
#include <core.reflection/member/constructor/ConstructorInfo.h>
namespace nspace{
  template<>
  struct add_default_constructor<void,true>{
    static void add(void * ){}
  };
  template<>
  struct add_default_constructor<void,false>{
    static void add(void * ){}
  };
template<typename T>
struct add_default_constructor<T,true>{
  
  static void add(TraitType<T> * type){

    struct ConstructorType : public TypedConstructorInfo<T>{
    public:
      nspace::Argument callImplementation(const  Arguments &  args)const override final{
        return InstanceType(new T());                                                                      
      }   
    }static instance;
  
    // static ConstructorInfo()   
  }
};
}

/*
#define DS_CONSTRUCTOR_STRUCT_DEFAULT(NAME)                                                                     \
typedef CurrentClassType DS_CONSTRUCTOR_OWNING_CLASS_NAME(NAME);                                              \
struct DS_CONSTRUCTOR_NAME(NAME):public nspace::TypedConstructorInfo<DS_CONSTRUCTOR_OWNING_CLASS_NAME(NAME)>{ \
DS_CLASS(DS_CONSTRUCTOR_NAME(NAME));                                                                          \
InstanceType construct()const{return InstanceType(new ConstructorClassType());}                               \
protected:                                                                                                    \
nspace::Argument callImplementation(const  Arguments &  args)const override final{                            \
auto method = typeof(CurrentClassType)->getMethod("construct");                                               \
return method->call(this,args);                                                                               \
}                                                                                                             \
reflect_method(construct);                                                                                    \
SINGLETON(DS_CONSTRUCTOR_NAME(NAME)){ }                                                                       \
};                                                                                                            \
DS_ONCE{                                                                                                      \
static std::shared_ptr<DS_CONSTRUCTOR_NAME(NAME)>  c = DS_CONSTRUCTOR_NAME(NAME)::instance();                 \
}*/
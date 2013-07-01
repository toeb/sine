#pragma once

#include <core.reflection/member/MemberInfo.h>
#include <core.reflection/type/Argument.h>
#include <core/template/function_traits.h>
#include <core.reflection/callable/ArgumentInfo.h>
#include <core.reflection/callable/Callable.h>

namespace nspace{

  class ConstructorInfo : public MemberInfo, public Callable{
  protected:
    // redefined because of proeprty Arguments
    typedef Callable::Arguments Args;
  public:
    typedef std::shared_ptr<const ArgumentInfo> argument_ptr;
    propdef std::vector<argument_ptr> basic_property(Arguments);
    property_reference(Arguments);
    argument_ptr argument(size_t i){
      if(Arguments().size()<=i)return argument_ptr();
      return Arguments()[i];
    }
    bool isValid()const override final{return true;}    
  };

  template<typename ClassType,typename Args>
  class TypedConstructorInfo {
    TypedConstructorInfo(){
      throw new std::exception("wrong usage for typed constructor info")
    }
  };
  template<typename ClassType>
  class TypedConstructorInfo<ClassType,void> : public ConstructorInfo{    
  public:
    Argument callImplementation(const std::vector<Argument> & args)const{
      if(args.size()!=0)throw std::exception("incorrect argument count while constructing type");
      return std::make_shared<ClassType>();
    }
  };
  template<typename ClassType,typename T1>
  class TypedConstructorInfo<ClassType, std::tuple<T1>> : public ConstructorInfo{
  public:
    
    TypedConstructorInfo(){
      static auto a0 = std::make_shared<TypedArgumentInfo<T1,0>>(); Arguments().push_back(a0);
    }
    Argument callImplementation(const std::vector<Argument> & args)const{
      if(args.size()!=1)throw std::exception("incorrect argument count while constructing type");
      return std::make_shared<ClassType>(
        (typename std::decay<T1>::type)args[0]
      );
    }
  };
  
  template<typename ClassType,typename T1,typename T2>
  class TypedConstructorInfo<ClassType, std::tuple<T1,T2>> : public ConstructorInfo{
  public:
    
    TypedConstructorInfo(){
      static auto a0 = std::make_shared<TypedArgumentInfo<T1,0>>(); Arguments().push_back(a0);
      static auto a1 = std::make_shared<TypedArgumentInfo<T2,1>>(); Arguments().push_back(a1);  
    }
    Argument callImplementation(const std::vector<Argument> & args)const{
      if(args.size()!=2)throw std::exception("incorrect argument count while constructing type");
      return std::make_shared<ClassType>(
        (typename std::decay<T1>::type)args[0],
        (typename std::decay<T2>::type)args[1]
      );
    }
  };
  template<typename ClassType,typename T1,typename T2,typename T3>
  class TypedConstructorInfo<ClassType,std::tuple<T1,T2,T3>> : public ConstructorInfo{
  public:
    TypedConstructorInfo(){
      static auto a0 = std::make_shared<TypedArgumentInfo<T1,0>>(); Arguments().push_back(a0);
      static auto a1 = std::make_shared<TypedArgumentInfo<T2,1>>(); Arguments().push_back(a1);
      static auto a2 = std::make_shared<TypedArgumentInfo<T3,2>>(); Arguments().push_back(a2);      
    }
    Argument callImplementation(const std::vector<Argument> & args)const{
      if(args.size()!=3)throw std::exception("incorrect argument count while constructing type");
      return std::make_shared<ClassType>(
        (typename std::decay<T1>::type)args[0],
        (typename std::decay<T2>::type)args[1],
        (typename std::decay<T3>::type)args[2]
      );
    }
  };
  /*
  class ConstructorInfo : public MemberInfo, public Callable{
  public:
    typedef std::vector<const Type*> basic_property(ArgumentTypes);
    bool isValid()const override final{return true;}
    ConstructorInfo(Type* owningType){
      owningType->Members()|=this;
      setOwningType(owningType);
      setName("constructor");
    }
  };

  template<typename ClassType>
  class TypedConstructorInfo : public ConstructorInfo{
  public:
    typedef std::shared_ptr<ClassType> InstanceType;
    typedef ClassType ConstructorClassType;
    TypedConstructorInfo():ConstructorInfo(const_cast<Type*>(typeof(ClassType))){

    }
  };



#define GENERIC_ARG_NAME(X) DS_CONCAT(a_,X)
#define GENERIC_ARG_DEF(X) traits:: nested_template arg<X>::type GENERIC_ARG_NAME(X)
#define GENERIC_ARG_TYPE(X) traits:: nested_template arg<X>::type

#define GENERIC_ARG_LIST(...) \
  DS_REDUCE_COMMA(GENERIC_ARG_DEF, DS_SEQUENCE(DS_MINUS_ONE(DS_NUM_ARGS(__VA_ARGS__))))
#define GENERIC_ARG_NAME_LIST(...) DS_REDUCE_COMMA(GENERIC_ARG_NAME, DS_SEQUENCE(DS_MINUS_ONE(DS_NUM_ARGS(__VA_ARGS__))))
#define GENERIC_ARG_TYPE_LIST(...) DS_REDUCE_COMMA(GENERIC_ARG_TYPE, DS_SEQUENCE(DS_MINUS_ONE(DS_NUM_ARGS(__VA_ARGS__))))

#define ADD_TYPE(X) types.push_back(typeof(X));

#define DS_CONSTRUCTOR_NAME(NAME) DS_CONCAT(Constructor,NAME)
#define DS_CONSTRUCTOR_OWNING_CLASS_NAME(NAME) DS_CONCAT(DS_CONSTRUCTOR_NAME(NAME),OwningClass)



#define DS_CONSTRUCTOR_STRUCT(NAME, ...)                                                                            \
  typedef CurrentClassType DS_CONSTRUCTOR_OWNING_CLASS_NAME(NAME);                                                  \
  struct DS_CONSTRUCTOR_NAME(NAME):public nspace::TypedConstructorInfo<DS_CONSTRUCTOR_OWNING_CLASS_NAME(NAME)>{     \
  struct Helper{                                                                                                    \
  void operator ()(__VA_ARGS__)const;                                                                               \
  };                                                                                                                \
  DS_CLASS(DS_CONSTRUCTOR_NAME(NAME));                                                                              \
  typedef nspace::function_traits<Helper> traits;                                                                   \
  InstanceType construct(GENERIC_ARG_LIST(__VA_ARGS__))const{                                                       \
  return InstanceType(new ConstructorClassType(GENERIC_ARG_NAME_LIST(__VA_ARGS__)));                                \
  }                                                                                                                 \
  protected:                                                                                                        \
  nspace::Argument callImplementation(const  Arguments &  args)const override final{                                \
  auto method = typeof(CurrentClassType)->getMethod("construct");                                                   \
  return method->call(this,args);                                                                                   \
  }                                                                                                                 \
  reflect_method(construct);                                                                                        \
  SINGLETON(DS_CONSTRUCTOR_NAME(NAME)){                                                                             \
  std::vector<const nspace::Type*> types;                                                                           \
  DS_FOREACH(ADD_TYPE,GENERIC_ARG_TYPE_LIST(__VA_ARGS__));                                                          \
  setArgumentTypes(types);                                                                                          \
  }                                                                                                                 \
  };                                                                                                                \
  DS_ONCE{                                                                                                          \
  static std::shared_ptr<DS_CONSTRUCTOR_NAME(NAME)>  c = DS_CONSTRUCTOR_NAME(NAME)::instance();                     \
  }

#define DS_CONSTRUCTOR_STRUCT_DEFAULT(NAME)                                                                         \
  struct DS_CONSTRUCTOR_NAME(NAME):public nspace::TypedConstructorInfo<CurrentClassType>{                           \
  protected:                                                                                                        \
  nspace::Argument callImplementation(const  Arguments &  args)const override final{                                \
    return InstanceType(new ConstructorClassType());                                                                \
  }                                                                                                                 \
  SINGLETON(DS_CONSTRUCTOR_NAME(NAME)){ }                                                                           \
  };                                                                                                                \
  DS_ONCE{                                                                                                          \
  static std::shared_ptr<DS_CONSTRUCTOR_NAME(NAME)>  c = DS_CONSTRUCTOR_NAME(NAME)::instance();                     \
  }



#define reflected_constructor(...) DS_CONSTRUCTOR_STRUCT(__LINE__, DS_REST(__VA_ARGS__))  DS_EXPAND(DS_FIRST(__VA_ARGS__)) ( DS_EXPAND(DS_REST( __VA_ARGS__) ))
#define reflected_default_constructor(TYPE) DS_CONSTRUCTOR_STRUCT_DEFAULT(Default) TYPE()
  */
}
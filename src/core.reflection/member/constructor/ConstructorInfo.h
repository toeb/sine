#pragma once

#include <core.reflection/member/MemberInfo.h>
#include <core.reflection/type/Argument.h>
#include <core/template/function_traits.h>
#include <core.reflection/callable/Callable.h>

namespace nspace{

  struct ConstructorInfo : public MemberInfo, public Callable{
    typedef std::vector<const Type*> basic_property(ArgumentTypes);
    bool isValid()const override final{return true;}

  };

  template<typename ClassType>
  struct TypedConstructorInfo : public ConstructorInfo{
    TypedConstructorInfo(){
      auto type = const_cast<Type*>(typeof(ClassType));
      type->Members()|=this;
      setOwningType(type);
      setName("constructor");

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

  // Type::Helper
  // Type::
  // Type::construct

#define DS_CONSTRUCTOR_STRUCT(NAME, ...)                                                              \
  typedef CurrentClassType DS_CONSTRUCTOR_OWNING_CLASS_NAME(NAME);                                          \
  struct DS_CONSTRUCTOR_NAME(NAME):public nspace::TypedConstructorInfo<DS_CONSTRUCTOR_OWNING_CLASS_NAME(NAME)>{             \
  struct Helper{                                                                                \
  void operator ()(__VA_ARGS__)const;                                                       \
  };                                                                                            \
  DS_CLASS(DS_CONSTRUCTOR_NAME(NAME));                                                                         \
  typedef nspace::function_traits<Helper> traits;                                               \
  DS_CONSTRUCTOR_OWNING_CLASS_NAME(NAME) * construct(GENERIC_ARG_LIST(__VA_ARGS__))const{     /*the pointer here*/              \
  return new DS_CONSTRUCTOR_OWNING_CLASS_NAME(NAME)(GENERIC_ARG_NAME_LIST(__VA_ARGS__));                  \
  }                                                                                               \
  protected:                                                                                      \
  nspace::Argument callImplementation(const  Arguments &  args)const override final{                          \
  auto method = typeof(CurrentClassType)->getMethod("construct");                               \
  return method->call(this,args);                                            /*will not be correctly returned here*/   \
  }                                                                                               \
  reflect_method(construct);                                                                    \
  SINGLETON(DS_CONSTRUCTOR_NAME(NAME)){                                                                       \
  std::vector<const nspace::Type*> types;                                                       \
  DS_FOREACH(ADD_TYPE,GENERIC_ARG_TYPE_LIST(__VA_ARGS__));                                      \
  setArgumentTypes(types);                                                                      \
  }                                                                                               \
  };                                                                                              \
  DS_ONCE{                                                                                      \
  static std::shared_ptr<DS_CONSTRUCTOR_NAME(NAME)>  c = DS_CONSTRUCTOR_NAME(NAME)::instance();                             \
  }

#define DS_CONSTRUCTOR_STRUCT_DEFAULT(NAME)                                                                               \
  typedef CurrentClassType DS_CONSTRUCTOR_OWNING_CLASS_NAME(NAME);                                                     \
  struct DS_CONSTRUCTOR_NAME(NAME):public nspace::TypedConstructorInfo<DS_CONSTRUCTOR_OWNING_CLASS_NAME(NAME)>{       \
  DS_CLASS(DS_CONSTRUCTOR_NAME(NAME));                                                                           \
  std::shared_ptr<DS_CONSTRUCTOR_OWNING_CLASS_NAME(NAME)> construct()const{return std::shared_ptr<DS_CONSTRUCTOR_OWNING_CLASS_NAME(NAME)>(new DS_CONSTRUCTOR_OWNING_CLASS_NAME(NAME)());}        \
  protected:                                                                                                                \
  nspace::Argument callImplementation(const  Arguments &  args)const override final{                                                        \
  auto method = typeof(CurrentClassType)->getMethod("construct");                                                         \
  return method->call(this,args);                                                                                         \
  }                                                                                                                         \
  reflect_method(construct);                                                                                              \
  SINGLETON(DS_CONSTRUCTOR_NAME(NAME)){ }                                                                                 \
  };                                                                                                                        \
  DS_ONCE{                                                                                                                \
  static std::shared_ptr<DS_CONSTRUCTOR_NAME(NAME)>  c = DS_CONSTRUCTOR_NAME(NAME)::instance();                           \
  }



#define reflected_constructor(...) DS_CONSTRUCTOR_STRUCT(__LINE__, DS_REST(__VA_ARGS__))  DS_EXPAND(DS_FIRST(__VA_ARGS__)) ( DS_EXPAND(DS_REST( __VA_ARGS__) ))
#define reflected_default_constructor(TYPE) DS_CONSTRUCTOR_STRUCT_DEFAULT(Default) TYPE()
}
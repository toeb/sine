#include <core.testing.h>
#include <core.reflection.h>

#include <core/template/function_traits.h>

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

#define DS_CONSTRUCTOR_STRUCT(NAME, ...)                                                              \
  typedef CurrentClassType DS_CONSTRUCTOR_OWNING_CLASS_NAME(NAME);                                          \
struct DS_CONSTRUCTOR_NAME(NAME):public nspace::TypedConstructorInfo<DS_CONSTRUCTOR_OWNING_CLASS_NAME(NAME)>{             \
  struct Helper{                                                                                \
      void operator ()(__VA_ARGS__)const;                                                       \
  };                                                                                            \
  DS_CURRENT_CLASS(DS_CONSTRUCTOR_NAME(NAME));\
  typedef nspace::function_traits<Helper> traits;                                               \
  DS_CONSTRUCTOR_OWNING_CLASS_NAME(NAME) * construct(GENERIC_ARG_LIST(__VA_ARGS__))const{     /*the pointer here*/              \
    return new DS_CONSTRUCTOR_OWNING_CLASS_NAME(NAME)(GENERIC_ARG_NAME_LIST(__VA_ARGS__));                  \
}                                                                                               \
protected:                                                                                      \
  nspace::Argument call(std::vector<nspace::Argument> args)const{                          \
  auto method = typeof(CurrentClassType)->getMethod("construct");                               \
  return method->call(this,args);                                                                                         /*will not be correctly returned here*/   \
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


#define reflect_constructor(TYPE, ...) DS_CONSTRUCTOR_STRUCT(__LINE__, __VA_ARGS__)  TYPE ( __VA_ARGS__)



UNITTEST(a){
  struct A{
    reflect_type(A);
  public:
    reflect_constructor(public: A, int i, int j, int k){
      sum = i+j+k;
    }
    int sum ;
  }a(1,2,3);
  
  
  auto type = typeof(A);

  auto constructor = type->Constructors().first();

  int args[3] = {1,2,3};
  auto instance=   constructor->call(args);

  auto theA= instance.cast<A>();

}


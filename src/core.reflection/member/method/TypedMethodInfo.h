#pragma once

#include <core.reflection/member/method/MethodInfo.h>

namespace nspace{

  template<typename Method>
  struct TypedMethodInfo;

  template<typename ClassType, typename ReturnType>
  struct TypedMethodInfo<ReturnType(ClassType::*)()const>:public MethodInfo{
    TypedMethodInfo(){
      setReturnType(type_of<ReturnType>());
      setIsConst(true);
    }
    typedef ReturnType(ClassType::*MethodType)()const ;                                                   
    MethodType method;                                                                                                                        
    TypedMethodInfo(MethodType method):method(method){}                                                                                       
    Argument typedCall(ClassType * object, std::vector<Argument> args)const{                                                                       
      Argument result;                                                                                                                           
      return Argument(((*object).*method)()); 
    }                                                                                                                                         
    Argument call(void * object, std::vector<Argument> args )const{                                                                                
      return typedCall(static_cast<ClassType*>(object),args);                                                                                   
    }                                                                
  };

  template<typename ClassType, typename ReturnType>
  struct TypedMethodInfo<ReturnType(ClassType::*)()>:public MethodInfo{TypedMethodInfo(){
    setReturnType(type_of<ReturnType>());
    setIsConst(false);
  }
  typedef ReturnType(ClassType::*MethodType)() ;                                                   
  MethodType method;                                                                                                                        
  TypedMethodInfo(MethodType method):method(method){}                                                                                       
  Argument typedCall(ClassType * object, std::vector<Argument> args)const{                                                                       
    Argument result;                                                                                                                           
    return Argument(((*object).*method)()); 
  }                                                                                                                                         
  Argument call(void * object, std::vector<Argument> args )const{                                                                                
    return typedCall(static_cast<ClassType*>(object),args);                                                                                   
  }                                                                
  };

  template<typename ClassType>
  struct TypedMethodInfo<void(ClassType::*)()const>:public MethodInfo{
    typedef void(ClassType::*MethodType)()const ;             
    TypedMethodInfo(){
      setReturnType(type_of<void>());
      setIsConst(true);
    }
    MethodType method;                                                                                                                        
    TypedMethodInfo(MethodType method):method(method){}                                                                                       
    Argument typedCall(ClassType * object, std::vector<Argument> args)const{           
      ((*object).*method)(); 
      return Argument::VoidArgument();
    }                                                                                                                                         
    Argument call(void * object, std::vector<Argument> args )const{                                                                                
      return typedCall(static_cast<ClassType*>(object),args);                                                                                   
    }                                                                
  };
  template<typename ClassType>
  struct TypedMethodInfo<void(ClassType::*)()>:public MethodInfo{
    TypedMethodInfo(){
      setReturnType(type_of<void>());
      setIsConst(false);
    }
    typedef void(ClassType::*MethodType)() ;                                                   
    MethodType method;                                                                                                                        
    TypedMethodInfo(MethodType method):method(method){}                                                                                       
    Argument typedCall(ClassType * object, std::vector<Argument> args)const{           
      ((*object).*method)(); 
      return Argument::VoidArgument();
    }                                                                                                                                         
    Argument call(void * object, std::vector<Argument> args )const{                                                                                
      return typedCall(static_cast<ClassType*>(object),args);                                                                                   
    }                                                                
  };





#define DS_TYPED_METHOD_INFO_ADD_ARGUMENT(X) argumentTypes().push_back(type_of<X>());
#define DS_TYPED_METHOD_INFO_PASS_ARG(X) args[X]
#define DS_TYPED_METHOD_INFO_CHECK_ARG(X) if(!args[X].isValid())return Argument();
#define DS_TYPED_METHOD_INFO(...)                                                                                                            \
  /* Specialization for const method with non void return type and arbirtray arguments*/                                                     \
  template<typename ClassType, typename ReturnType,DS_REDUCE_COMMA(DS_ADD_TYPENAME,__VA_ARGS__)>                                             \
  struct TypedMethodInfo<ReturnType(ClassType::*)(DS_REDUCE_COMMA(DS_NOOP,__VA_ARGS__)) const>:public MethodInfo{                            \
  typedef ReturnType(ClassType::*MethodType)(DS_REDUCE_COMMA(DS_NOOP,__VA_ARGS__))const ;                                                    \
  MethodType method;                                                                                                                         \
  TypedMethodInfo(MethodType method):method(method){                                                                                         \
  setReturnType(type_of<ReturnType>());                                                                                                      \
  DS_FOREACH(DS_TYPED_METHOD_INFO_ADD_ARGUMENT,__VA_ARGS__)                                                                                  \
  setIsConst(true);                                                                                                                          \
  }                                                                                                                                          \
  Argument typedCall(ClassType * object, std::vector<Argument> args)const{                                                                   \
  DS_FOREACH(DS_TYPED_METHOD_INFO_CHECK_ARG, DS_SEQUENCE(DS_MINUS_ONE(DS_NUM_ARGS(__VA_ARGS__))))                                            \
  return Argument(((*object).*method)(DS_REDUCE_COMMA(DS_TYPED_METHOD_INFO_PASS_ARG,DS_SEQUENCE(DS_MINUS_ONE(DS_NUM_ARGS(__VA_ARGS__))))));  \
  }                                                                                                                                          \
  Argument call(void * object, std::vector<Argument> args )const{                                                                            \
  return typedCall(static_cast<ClassType*>(object),args);                                                                                    \
  }                                                                                                                                          \
  };                                                                                                                                         \
  /* Specialization for non-const method with non void return type and arbirtray arguments*/                                                 \
  template<typename ClassType, typename ReturnType,DS_REDUCE_COMMA(DS_ADD_TYPENAME,__VA_ARGS__)>                                             \
  struct TypedMethodInfo<ReturnType(ClassType::*)(DS_REDUCE_COMMA(DS_NOOP,__VA_ARGS__))>:public MethodInfo{                                  \
  typedef ReturnType(ClassType::*MethodType)(DS_REDUCE_COMMA(DS_NOOP,__VA_ARGS__));                                                          \
  MethodType method;                                                                                                                         \
  TypedMethodInfo(MethodType method):method(method){                                                                                         \
  setReturnType(type_of<ReturnType>());                                                                                                      \
  DS_FOREACH(DS_TYPED_METHOD_INFO_ADD_ARGUMENT,__VA_ARGS__)                                                                                  \
  setIsConst(false);                                                                                                                         \
  }                                                                                                                                          \
  Argument typedCall(ClassType * object, std::vector<Argument> args)const{                                                                   \
  DS_FOREACH(DS_TYPED_METHOD_INFO_CHECK_ARG, DS_SEQUENCE(DS_MINUS_ONE(DS_NUM_ARGS(__VA_ARGS__))))                                            \
  return Argument(((*object).*method)(DS_REDUCE_COMMA(DS_TYPED_METHOD_INFO_PASS_ARG,DS_SEQUENCE(DS_MINUS_ONE(DS_NUM_ARGS(__VA_ARGS__))))));  \
  }                                                                                                                                          \
  Argument call(void * object, std::vector<Argument> args )const{                                                                            \
  return typedCall(static_cast<ClassType*>(object),args);                                                                                    \
  }                                                                                                                                          \
  };                                                                                                                                         \
  /* Specialization for const method with  void return type and arbirtray arguments*/                                                        \
  template<typename ClassType,DS_REDUCE_COMMA(DS_ADD_TYPENAME,__VA_ARGS__)>                                                                  \
  struct TypedMethodInfo<void(ClassType::*)(DS_REDUCE_COMMA(DS_NOOP,__VA_ARGS__))const>:public MethodInfo{                                   \
  typedef void(ClassType::*MethodType)(DS_REDUCE_COMMA(DS_NOOP,__VA_ARGS__))const ;                                                          \
  MethodType method;                                                                                                                         \
  TypedMethodInfo(MethodType method):method(method){                                                                                         \
  setReturnType(type_of<void>());                                                                                                            \
  DS_FOREACH(DS_TYPED_METHOD_INFO_ADD_ARGUMENT,__VA_ARGS__)                                                                                  \
  setIsConst(true);                                                                                                                          \
  }                                                                                                                                          \
  Argument typedCall(ClassType * object, std::vector<Argument> args)const{                                                                   \
  DS_FOREACH(DS_TYPED_METHOD_INFO_CHECK_ARG, DS_SEQUENCE(DS_MINUS_ONE(DS_NUM_ARGS(__VA_ARGS__))))                                            \
  ((*object).*method)(DS_REDUCE_COMMA(DS_TYPED_METHOD_INFO_PASS_ARG,DS_SEQUENCE(DS_MINUS_ONE(DS_NUM_ARGS(__VA_ARGS__)))));                   \
  return Argument::VoidArgument();                                                                                                           \
  }                                                                                                                                          \
  Argument call(void * object, std::vector<Argument> args )const{                                                                            \
  return typedCall(static_cast<ClassType*>(object),args);                                                                                    \
  }                                                                                                                                          \
  };                                                                                                                                         \
  /* Specialization for non-const method with void return type and arbirtray arguments*/                                                     \
  template<typename ClassType,DS_REDUCE_COMMA(DS_ADD_TYPENAME,__VA_ARGS__)>                                                                  \
  struct TypedMethodInfo<void(ClassType::*)(DS_REDUCE_COMMA(DS_NOOP,__VA_ARGS__))>:public MethodInfo{                                        \
  typedef void(ClassType::*MethodType)(DS_REDUCE_COMMA(DS_NOOP,__VA_ARGS__)) ;                                                               \
  MethodType method;                                                                                                                         \
  TypedMethodInfo(MethodType method):method(method){                                                                                         \
  setReturnType(type_of<void>());                                                                                                            \
  DS_FOREACH(DS_TYPED_METHOD_INFO_ADD_ARGUMENT,__VA_ARGS__)                                                                                  \
  setIsConst(false);                                                                                                                         \
  }                                                                                                                                          \
  Argument typedCall(ClassType * object, std::vector<Argument> args)const{                                                                   \
  DS_FOREACH(DS_TYPED_METHOD_INFO_CHECK_ARG, DS_SEQUENCE(DS_MINUS_ONE(DS_NUM_ARGS(__VA_ARGS__))))                                            \
  ((*object).*method)(DS_REDUCE_COMMA(DS_TYPED_METHOD_INFO_PASS_ARG,DS_SEQUENCE(DS_MINUS_ONE(DS_NUM_ARGS(__VA_ARGS__)))));                   \
  return Argument::VoidArgument();                                                                                                           \
  }                                                                                                                                          \
  Argument call(void * object, std::vector<Argument> args )const{                                                                            \
  return typedCall(static_cast<ClassType*>(object),args);                                                                                    \
  }                                                                                                                                          \
  };      

  DS_TYPED_METHOD_INFO(A1)
    DS_TYPED_METHOD_INFO(A1,A2)
    DS_TYPED_METHOD_INFO(A1,A2,A3)
    DS_TYPED_METHOD_INFO(A1,A2,A3,A4)
    DS_TYPED_METHOD_INFO(A1,A2,A3,A4,A5)
    DS_TYPED_METHOD_INFO(A1,A2,A3,A4,A5,A6)
    DS_TYPED_METHOD_INFO(A1,A2,A3,A4,A5,A6,A7)
    DS_TYPED_METHOD_INFO(A1,A2,A3,A4,A5,A6,A7,A8)
    DS_TYPED_METHOD_INFO(A1,A2,A3,A4,A5,A6,A7,A8,A9)

}
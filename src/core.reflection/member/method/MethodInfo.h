#pragma once
#include <core.reflection/member/MemberInfo.h>

namespace nspace{
 /* // MethodInfo represents a method of a class
  // TODO:  allow multiple arguments and return values
  // TODO get away from inheritance and use std::functions or something similar
  class MethodInfo : public virtual MemberInfo{
    TYPED_OBJECT(MethodInfo);
  public:
    // the call method must be implemented by a subclass
    virtual bool call(Object * object, void * arguments=0, void ** returnvalue=0)const=0;
    // the unsafe call method assumes object is a pointer to the concrete type
    virtual bool unsafeCall(void * object, void * arguments=0, void** returnvalue=0)const=0;
  };
  */
  
  struct Argument{

    template<typename T> Argument(const T & data):data(new T(data)),type(type_of<T>()){}
    template<typename T> Argument(std::shared_ptr<T> data):data(std::static_pointer_cast<void>(data)),type(type_of<T>()){}
    Argument(std::shared_ptr<void> data, const Type * type):data(data),type(type){}
    Argument():type(0){}

    static const Argument & VoidArgument(){
      // create a unique instance for argument
      static std::unique_ptr<Argument> instance(new Argument(std::shared_ptr<void>((void*)new int),0));
      return *instance.get();
    }


    bool isValid()const{return (bool)data;}

    template<typename T> operator const T & ()const{
      return *std::static_pointer_cast<T>(data); 
    }

    template<typename T> operator T & (){
      return *std::static_pointer_cast<T>(data); 
    }



    std::shared_ptr<void> data;
    const Type * type;
  };
  /*struct Argument:public IArgument{
  Argument():_data(0),_type(0){}

  std::shared_ptr<void> _data;
  const Type * _type;
  std::shared_ptr<void> data(){return _data;}
  const Type * type()const{return _type;}
  };*/


  class MethodInfo : public MemberInfo{
    DS_CLASS(MemberInfo)
  public:
    template<typename Container>
    Argument call(void * object, Container & container=std::vector<Argument>())const{
      std::vector<Argument> args;
      for(auto it = std::begin(container); it!=std::end(container);it++){
        args.push_back(*it);
      }
      return call(object,args);
    }
    template<typename Container>
    Argument call(Object * object, Container & container=std::vector<Argument>())const{
      auto ptr = object->getType()->toRawDerivedPointer(object);
      return call<Container>(object,args);
    }
    Argument call(void * object)const{
      std::vector<Argument> args;
      return call(object,args);
    }

    Argument call(Object * object){
      auto ptr = object->getType()->toRawDerivedPointer(object);
      call(ptr);

    }
    

  protected:
    virtual Argument call(void * object, std::vector<Argument> arguments)const=0;
  };

  template<typename Method>
  struct TypedMethodInfo;

  template<typename ClassType, typename ReturnType>
  struct TypedMethodInfo<ReturnType(ClassType::*)()const>:public MethodInfo{
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
  struct TypedMethodInfo<ReturnType(ClassType::*)()>:public MethodInfo{
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








#define DS_TYPED_METHOD_INFO_PASS_ARG(X) args[X]
#define DS_TYPED_METHOD_INFO_CHECK_ARG(X) if(!args[X].isValid())return Argument();
#define DS_TYPED_METHOD_INFO(...)                                                                                                             \
  template<typename ClassType, typename ReturnType,DS_REDUCE_COMMA(DS_ADD_TYPENAME,__VA_ARGS__)>                                              \
  struct TypedMethodInfo<ReturnType(ClassType::*)(DS_REDUCE_COMMA(DS_NOOP,__VA_ARGS__)) const>:public MethodInfo{                             \
  typedef ReturnType(ClassType::*MethodType)(DS_REDUCE_COMMA(DS_NOOP,__VA_ARGS__))const ;                                                     \
  MethodType method;                                                                                                                          \
  TypedMethodInfo(MethodType method):method(method){}                                                                                         \
  Argument typedCall(ClassType * object, std::vector<Argument> args)const{                                                                    \
  DS_FOREACH(DS_TYPED_METHOD_INFO_CHECK_ARG, DS_SEQUENCE(DS_MINUS_ONE(DS_NUM_ARGS(__VA_ARGS__))))                                             \
  return Argument(((*object).*method)(DS_REDUCE_COMMA(DS_TYPED_METHOD_INFO_PASS_ARG,DS_SEQUENCE(DS_MINUS_ONE(DS_NUM_ARGS(__VA_ARGS__))))));   \
  }                                                                                                                                           \
  Argument call(void * object, std::vector<Argument> args )const{                                                                             \
  return typedCall(static_cast<ClassType*>(object),args);                                                                                     \
  }                                                                                                                                           \
  };                                                                                                                                          \
  template<typename ClassType, typename ReturnType,DS_REDUCE_COMMA(DS_ADD_TYPENAME,__VA_ARGS__)>                                              \
  struct TypedMethodInfo<ReturnType(ClassType::*)(DS_REDUCE_COMMA(DS_NOOP,__VA_ARGS__))>:public MethodInfo{                                   \
  typedef ReturnType(ClassType::*MethodType)(DS_REDUCE_COMMA(DS_NOOP,__VA_ARGS__));                                                           \
  MethodType method;                                                                                                                          \
  TypedMethodInfo(MethodType method):method(method){}                                                                                         \
  Argument typedCall(ClassType * object, std::vector<Argument> args)const{                                                                    \
  DS_FOREACH(DS_TYPED_METHOD_INFO_CHECK_ARG, DS_SEQUENCE(DS_MINUS_ONE(DS_NUM_ARGS(__VA_ARGS__))))                                             \
  return Argument(((*object).*method)(DS_REDUCE_COMMA(DS_TYPED_METHOD_INFO_PASS_ARG,DS_SEQUENCE(DS_MINUS_ONE(DS_NUM_ARGS(__VA_ARGS__))))));   \
  }                                                                                                                                           \
  Argument call(void * object, std::vector<Argument> args )const{                                                                             \
  return typedCall(static_cast<ClassType*>(object),args);                                                                                     \
  }                                                                                                                                           \
  };                                                                                                                                          \
  template<typename ClassType,DS_REDUCE_COMMA(DS_ADD_TYPENAME,__VA_ARGS__)>                                                                   \
  struct TypedMethodInfo<void(ClassType::*)(DS_REDUCE_COMMA(DS_NOOP,__VA_ARGS__))const>:public MethodInfo{                                    \
  typedef void(ClassType::*MethodType)(DS_REDUCE_COMMA(DS_NOOP,__VA_ARGS__))const ;                                                           \
  MethodType method;                                                                                                                          \
  TypedMethodInfo(MethodType method):method(method){}                                                                                         \
  Argument typedCall(ClassType * object, std::vector<Argument> args)const{                                                                    \
  DS_FOREACH(DS_TYPED_METHOD_INFO_CHECK_ARG, DS_SEQUENCE(DS_MINUS_ONE(DS_NUM_ARGS(__VA_ARGS__))))                                             \
  ((*object).*method)(DS_REDUCE_COMMA(DS_TYPED_METHOD_INFO_PASS_ARG,DS_SEQUENCE(DS_MINUS_ONE(DS_NUM_ARGS(__VA_ARGS__)))));                    \
  return Argument::VoidArgument();                                                                                                            \
  }                                                                                                                                           \
  Argument call(void * object, std::vector<Argument> args )const{                                                                             \
  return typedCall(static_cast<ClassType*>(object),args);                                                                                     \
  }                                                                                                                                           \
  };                                                                                                                                          \
  template<typename ClassType,DS_REDUCE_COMMA(DS_ADD_TYPENAME,__VA_ARGS__)>                                                                   \
  struct TypedMethodInfo<void(ClassType::*)(DS_REDUCE_COMMA(DS_NOOP,__VA_ARGS__))>:public MethodInfo{                                         \
  typedef void(ClassType::*MethodType)(DS_REDUCE_COMMA(DS_NOOP,__VA_ARGS__)) ;                                                                \
  MethodType method;                                                                                                                          \
  TypedMethodInfo(MethodType method):method(method){}                                                                                         \
  Argument typedCall(ClassType * object, std::vector<Argument> args)const{                                                                    \
  DS_FOREACH(DS_TYPED_METHOD_INFO_CHECK_ARG, DS_SEQUENCE(DS_MINUS_ONE(DS_NUM_ARGS(__VA_ARGS__))))                                             \
  ((*object).*method)(DS_REDUCE_COMMA(DS_TYPED_METHOD_INFO_PASS_ARG,DS_SEQUENCE(DS_MINUS_ONE(DS_NUM_ARGS(__VA_ARGS__)))));                    \
  return Argument::VoidArgument();                                                                                                            \
  }                                                                                                                                           \
  Argument call(void * object, std::vector<Argument> args )const{                                                                             \
  return typedCall(static_cast<ClassType*>(object),args);                                                                                     \
  }                                                                                                                                           \
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
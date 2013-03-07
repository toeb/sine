#pragma once

#include <core.reflection/type/Argument.h>

// preprocessor implementation
#define DS_CALLABLE_TEMPLATE_CALL_NAME operator()
#define DS_CALLABLE_TEMPLATE_CALL_TYPE_NAME_I(X) DS_CONCAT(T,X)
#define DS_CALLABLE_TEMPLATE_CALL_TYPE_NAME_TEMPLATE_I(X) typename DS_CALLABLE_TEMPLATE_CALL_TYPE_NAME_I(X)
#define DS_CALLABLE_TEMPLATE_CALL_VAR_NAME_I(X) DS_CONCAT(arg,X)
#define DS_CALLABLE_TEMPLATE_CALL_SIGNATURE_ARG_I(X) DS_CALLABLE_TEMPLATE_CALL_TYPE_NAME_I(X) DS_CALLABLE_TEMPLATE_CALL_VAR_NAME_I(X)
#define DS_CALLABLE_TEMPLATE_CALL_SIGNATURE_N(N) \
  template< DS_REDUCE_COMMA( DS_CALLABLE_TEMPLATE_CALL_TYPE_NAME_TEMPLATE_I, DS_SEQUENCE(DS_MINUS_ONE(N)))> \
  Argument DS_CALLABLE_TEMPLATE_CALL_NAME(DS_REDUCE_COMMA(DS_CALLABLE_TEMPLATE_CALL_SIGNATURE_ARG_I, DS_SEQUENCE(DS_MINUS_ONE(N))))


#define DS_CALLABLE_TEMPLATE_CALL_IMP_N(N) \
    {\
    Argument args[N]={DS_REDUCE_COMMA(DS_CALLABLE_TEMPLATE_CALL_VAR_NAME_I,DS_SEQUENCE(DS_MINUS_ONE(N)))};   \
    return call(args);\
    }


#define DS_CALLABLE_TEMPLATE_CALL_N(N)                         \
  DS_CALLABLE_TEMPLATE_CALL_SIGNATURE_N(N)const              \
  DS_CALLABLE_TEMPLATE_CALL_IMP_N(N)                         \
  DS_CALLABLE_TEMPLATE_CALL_SIGNATURE_N(N)                   \
  DS_CALLABLE_TEMPLATE_CALL_IMP_N(N)



namespace nspace{
  struct Callable{    
    reflect_type(Callable);
    // typedef std::vector<const Type*> basic_property(ArgumentTypes);
  public:
    typedef std::vector<Argument> Arguments;



    virtual ~Callable(){}
    Argument operator()();    
    Argument operator()()const;    
    DS_FOREACH(DS_CALLABLE_TEMPLATE_CALL_N, 1,2,3,4,5,6,7,8,9,10);





    Argument call();    
    Argument call()const;    
    template<typename TContainer> Argument call(TContainer & container);
    template<typename TContainer> Argument call(TContainer & container)const;






    virtual bool isValid()const=0;
    virtual Argument callImplementation(const Arguments & args);
    virtual Argument callImplementation(const Arguments & args)const;


  };

}



// impl
namespace nspace{

  template<typename TContainer> Argument Callable::call(TContainer & container){
    Arguments vec;
    for(auto it = std::begin(container); it!=std::end(container); it++){
      vec.push_back(*it);
    }
    return callImplementation(vec);
  }
  template<typename TContainer> Argument Callable::call(TContainer & container)const{
    Arguments vec;
    for(auto it = std::begin(container); it!=std::end(container); it++){
      vec.push_back(*it);
    }
    return callImplementation(vec);
  } 

}
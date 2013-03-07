#pragma once

#include <core.reflection/type/Argument.h>
namespace nspace{
  struct Callable{    
    reflect_type(Callable);
   // typedef std::vector<const Type*> basic_property(ArgumentTypes);
  public:
    typedef std::vector<Argument> Arguments;



    virtual ~Callable(){}
    Argument operator()();    
    Argument operator()()const;    
    template<typename TContainer> Argument operator()(TContainer & container);
    template<typename TContainer> Argument operator()(TContainer & container)const;
    
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
  template<typename TContainer> Argument Callable::operator()(TContainer & container){
    Arguments vec;
    for(auto it = std::begin(container); it!=std::end(container); it++){
      vec.push_back(*it);
    }
    return callImplementation(vec);
  }
  template<typename TContainer> Argument Callable::operator()(TContainer & container)const{
    Arguments vec;
    for(auto it = std::begin(container); it!=std::end(container); it++){
      vec.push_back(*it);
    }
    return callImplementation(vec);
  } 
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
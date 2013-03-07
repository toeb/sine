#pragma once
#include <config.h>
#include <memory>

namespace nspace{
  class Type;
  //todo rename to ObjectHandle
  struct Argument{
//    std::function<void()> deleter;

    template<typename T> Argument(const T & data);
    template<typename T> Argument(std::shared_ptr<T> data);
    Argument(std::shared_ptr<void> data, const Type * type);
    Argument();
    ~Argument(){
  //    if((bool)deleter)deleter();
    }
    
    


    static const Argument & VoidArgument();    
    bool isValid()const;
    template<typename T> operator const T & ()const;
    template<typename T> operator T & ();

    template<typename T> operator  std::shared_ptr<const T> ()const{
      return cast<const T>();
    }

    template<typename T> operator  std::shared_ptr<T>  (){return cast<T>();}

    template<typename T> std::shared_ptr<T>  cast();
    template<typename T> std::shared_ptr<const T> cast()const;
    
    std::shared_ptr<void> data;
    const Type * type;
  };



}


// template implementation
#include <core.reflection/type/TypeInfo.h>

namespace nspace{
  template<typename T> Argument::Argument(const T & data):data(std::static_pointer_cast<void>(std::shared_ptr<T>(new T(data)))),type(type_of<T>()){
    
  }
  template<typename T> Argument::Argument(std::shared_ptr<T> data):data(std::static_pointer_cast<void>(data)),type(type_of<T>()){
  
  }
  template<typename T> Argument::operator const T & ()const{
    return *cast<T>(); 
  }
  template<typename T> Argument::operator T & (){
    return *cast<T>(); 
  }
  
  
  template<typename T>  std::shared_ptr<T>  Argument::cast(){return std::static_pointer_cast<T>(data);}
  template<typename T>  std::shared_ptr< const T>   Argument::cast()const{return std::static_pointer_cast<T>(data);}
}

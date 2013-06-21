#pragma once
#include <core.reflection/type/Argument.h>

// template implementation
#include <core.reflection/type/TypeInfo.h>

namespace nspace{
  template<typename T> Argument::Argument(const T & data):data(std::static_pointer_cast<void>(std::shared_ptr<T>(new T(data)))),type(type_of<T>()){

  }
  template<typename T> Argument::Argument(std::shared_ptr<T> data):data(std::static_pointer_cast<void>(data)),type(type_of<T>()){

  }
  template<typename T> Argument::operator const T & ()const{
    if(!(bool)data)std::cerr<<"dereferencing null ptr"<<std::endl;
    return *cast<T>(); 
  }
  template<typename T> Argument::operator T & (){
    if(!(bool)data)std::cerr<<"dereferencing null ptr"<<std::endl;
    return *cast<T>(); 
  }


  template<typename T> Argument::operator  std::shared_ptr<const T> ()const{
    return cast<const T>();    }


  template<typename T> Argument::operator  std::shared_ptr<T>  (){return cast<T>();}

  template<typename T>  std::shared_ptr<T>  Argument::cast(){return std::static_pointer_cast<T>(data);}
  template<typename T>  std::shared_ptr< const T>   Argument::cast()const{return std::static_pointer_cast<T>(data);}
}

#pragma once

#include <core.reflection/type/Type.h>

namespace nspace{

  struct Argument{
    template<typename T> Argument(const T & data);
    template<typename T> Argument(std::shared_ptr<T> data);
    Argument(std::shared_ptr<void> data, const Type * type);
    Argument();
    static const Argument & VoidArgument();    
    bool isValid()const;
    template<typename T> operator const T & ()const;
    template<typename T> operator T & ();

    std::shared_ptr<void> data;
    const Type * type;
  };



}


// template implementation
#include <core.reflection/type/TypeInfo.h>

namespace nspace{
  template<typename T> Argument::Argument(const T & data):data(new T(data)),type(type_of<T>()){
  
  }
  template<typename T> Argument::Argument(std::shared_ptr<T> data):data(std::static_pointer_cast<void>(data)),type(type_of<T>()){
  
  }
  template<typename T> Argument::operator const T & ()const{
    return *std::static_pointer_cast<T>(data); 
  }
  template<typename T> Argument::operator T & (){
    return *std::static_pointer_cast<T>(data); 
  }
}

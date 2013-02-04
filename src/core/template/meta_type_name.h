#pragma once

#include <config.h>


namespace nspace{

  template<typename T>
  struct meta_type_name{
    static const std::string & value(){
      static std::string name = T::getTypeName();
      return name;
    }
  };
}
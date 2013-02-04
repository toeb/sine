#pragma once

#include <config.h>
namespace nspace{
  
  template<typename T>
  struct meta_type_tostring{
    static void toString(const void * object, std::ostream& stream){
      stream <<static_cast<const T*>(object);
    }
  };

}
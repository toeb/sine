#pragma once

#include <config.h>
namespace nspace{
  

  template<typename T>
  struct meta_type_construction{
    static const bool constructible = default_constructor<T>::isConstructible;
    static std::shared_ptr<void> construct(){
      return default_constructor<T>::construct();
       //return std::shared_ptr<void>();
    }
  };
}
#pragma once

#include <cstddef>
#include <config.h>
#include <core/template/is_singleton.h>
namespace nspace{
  

    // returns a new instance of T if T is defaultconstructible. else returns 0; also work for singletons
  // TODO: this will cause errors for all types that are only privately constructible
  template<typename T, bool IsDefaultConstructible=std::is_default_constructible<T>::value && !std::is_abstract<T>::value, bool Singleton=is_singleton<T>::value>
  struct default_constructor{    
    const static bool isConstructible=false;
    static std::shared_ptr<T> construct(){
      return std::shared_ptr<T>();
    }
  };


  //Specialization for non singleton default constructable type
  template<typename T>
  struct default_constructor<T,true,false>{
    const static bool isConstructible=true;
    static std::shared_ptr<T> construct(){
      return std::shared_ptr<T>(new T());
    }
  };

  //specialization for singleton type.
  template<typename T>
  struct default_constructor<T,true,true>{
    const static bool isConstructible=true;
    static std::shared_ptr<T> construct(){
      return std::shared_ptr<T>(T::instance());
    }
  };
}
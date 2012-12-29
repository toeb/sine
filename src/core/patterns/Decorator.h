#pragma once
#include <core/Object.h>
namespace nspace{
  template<typename T>
  class Decorator : public  T{
    T & _base;
  protected:
    T & base(){
      return _base;
    }
    const T& base()const{
      return _base;
    }
    Decorator(T & base):_base(base){
    }
  };
}
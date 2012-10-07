#pragma once

#include <config.h>

namespace nspace{
  template<typename Derived>
  class Derivable{
  private:
    Derived & _derived;
  public:
    Derivable():_derived(*static_cast<Derived*>(this)){}
    inline Derived & derived(){return _derived;}
    inline const Derived & derived()const{return _derived;}
  };
}
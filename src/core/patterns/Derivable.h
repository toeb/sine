#pragma once

#include <config.h>

namespace nspace{
  template<typename Derived>
  class Derivable{
  public:
    typedef Derived derived_type;
    typedef derived_type* derived_ptr;
  private:
    derived_ptr _derived;
  public:
    Derivable():_derived(static_cast<derived_ptr>(this)){}
    
    inline derived_ptr derived(){return _derived;}
    inline const derived_ptr derived()const{return _derived;}
  };
}
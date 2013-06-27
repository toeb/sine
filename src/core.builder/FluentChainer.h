#pragma once
#include <config.h>
namespace nspace{
  namespace core{
    namespace builder{
      template<typename Derived>
      class FluentChainer {
      public:
        typedef typename Derived * derived_ptr;
        typedef typename Derived derived_type;
      private:
        derived_ptr _derived;
      protected:
        FluentChainer(derived_ptr derived):_derived(derived){}
        ~FluentChainer(){_derived=0;}
      public:
        derived_ptr derived(){return _derived;}
        const derived_ptr derived()const{return _derived;}
      };
    }
  }
}
#pragma once
#include <core.builder/FluentChainer.h>
namespace nspace{
  namespace core{
    namespace builder{
      template<typename Derived>
      class FluentFunctionChainer : public FluentChainer<Derived>{
      protected:
        FluentFunctionChainer(derived_ptr derived):FluentChainer(derived){}
      public:
        derived_ptr call(std::function<void()> function){
          function();
          return derived();
        }
      };
    }
  }
}
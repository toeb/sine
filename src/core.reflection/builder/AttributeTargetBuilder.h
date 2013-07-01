#pragma once
#include <core.builder/Builder.h>
namespace nspace{
  namespace core{
    namespace reflection{
      namespace builder{
        template<typename AttributeType,typename Derived> class AttributeBuilder;
        template<typename Derived, typename ResultType>
        class AttributeTargetBuilder:
          public core::builder::Builder<Derived, ResultType>
        {
        public:
          AttributeTargetBuilder(derived_ptr derived);
          AttributeTargetBuilder(derived_ptr derived, result_ptr result);

          template<typename AttributeType>
          AttributeBuilder<AttributeType,Derived> attribute();
        };
      }
    }
  }
}
#pragma once
#include <core.builder/Builder.h>
#include <core.builder/FluentFunctionChainer.h>
#include <core.reflection/builder/AttributeBuilder.h>
namespace nspace{
  namespace core{
    namespace reflection{
      namespace builder{
        template<typename Derived, typename ResultType>
        class AttributeTargetBuilder:
          public core::builder::Builder<Derived, ResultType>
        {
        public:
          AttributeTargetBuilder(derived_ptr derived):
            nspace::core::builder::Builder(derived){
          
          }
          AttributeTargetBuilder(derived_ptr derived, result_ptr result):
            nspace::core::builder::Builder<Derived,ResultType>(derived,result){
          
          }

          template<typename AttributeType>
          AttributeBuilder<AttributeType,Derived> attribute(){
            AttributeBuilder<AttributeType,Derived> result;
            return result;
          }
        };
      }
    }
  }
}
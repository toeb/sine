#pragma once
#include "AttributeTargetBuilder.h"
#include <core.reflection/builder/AttributeBuilder.h>
namespace nspace{
  namespace core{
    namespace reflection{
      namespace builder{
        template<typename Derived, typename ResultType>
        AttributeTargetBuilder<Derived,ResultType>::AttributeTargetBuilder(derived_ptr derived):
          nspace::core::builder::Builder<Derived,ResultType>(derived){

        }
        template<typename Derived, typename ResultType>
        AttributeTargetBuilder<Derived,ResultType>::AttributeTargetBuilder(derived_ptr derived, result_ptr result):
          nspace::core::builder::Builder<Derived,ResultType>(derived,result){

        }
        
        template<typename Derived, typename ResultType>
        template<typename AttributeType>
        AttributeBuilder<AttributeType,Derived> AttributeTargetBuilder<Derived,ResultType>::attribute(){
          AttributeBuilder<AttributeType,Derived> result;
          return result;
        }
      }
    }
  }
}
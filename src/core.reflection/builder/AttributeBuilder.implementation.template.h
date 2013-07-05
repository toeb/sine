#pragma once
#include "AttributeBuilder.h"
namespace nspace{
  namespace core{
    namespace reflection{
      namespace builder{


        template<typename AttributeType,typename ParentBuilder>
        auto AttributeBuilder<AttributeType,ParentBuilder>::name(const std::string & n)->derived_ptr{
          result()->setAttributeName(n);
          return derived();
        }
        template<typename AttributeType,typename ParentBuilder>
        auto AttributeBuilder<AttributeType,ParentBuilder>::operator()(std::function<void(attribute_type &)> func)->derived_ptr{
          if(!(bool)result())throw new std::exception("cannot call function because result() is not set");
          func(*result());
          return derived();
        }
      }
    }
  }
}
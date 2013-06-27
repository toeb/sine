#pragma once

#include <core.builder/NestedBuilder.h>
namespace nspace{
  namespace core{
    namespace reflection{
      namespace builder{
        template<typename AttributeType,typename ParentBuilder>
        class AttributeBuilder : public core::builder::NestedBuilder<AttributeBuilder<AttributeType,ParentBuilder>,ParentBuilder,AttributeType>{
          typedef typename AttributeType attribute_type;
        public:

          derived_ptr & name(const std::string & n){
            result()->setAttributeName(n);
          }
          derived_ptr & operator()(std::function<void(attribute_type &)> func){
            if(!(bool)result())throw new std::exception("cannot call function because result() is not set");
            func(*result());
            return *this;
          }
        };
      }
    }
  }
}
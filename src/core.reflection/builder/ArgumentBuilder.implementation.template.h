#pragma once
#include "ArgumentBuilder.h"
#include <core.reflection/callable/ArgumentInfo.h>

#include <memory>
namespace nspace{
  namespace core{
    namespace reflection{
      namespace builder{
        template<typename Callable, typename ParentBuilder, size_t ArgIndex>
        auto ArgumentBuilder<Callable,ParentBuilder,ArgIndex>::createInstance()->result_ptr{
          return parent()->result()->argument(ArgIndex);
        }

     /*   template<typename T, typename Method, unsigned int ArgIndex>
        auto ArgumentBuilder<T,Method,ArgIndex>::defaultValue(const argument_type & value)->derived_ptr{
          return defaultValue((Argument)value);
        }
        template<typename T, typename Method, unsigned int ArgIndex>
        auto ArgumentBuilder<T,Method,ArgIndex>::defaultValue(std::shared_ptr<argument_type> value)->derived_ptr{
          return defaultValue((Argument)value);
        }*/
        
        template<typename Callable, typename ParentBuilder, size_t ArgIndex>
        auto ArgumentBuilder<Callable,ParentBuilder,ArgIndex>::defaultValue(Argument argument)->derived_ptr{
          result()->setDefaultValue(argument);
          return derived();
        }

        template<typename Callable, typename ParentBuilder, size_t ArgIndex>
        ArgumentBuilder<Callable,ParentBuilder,ArgIndex>::ArgumentBuilder(parent_ptr parent):
          core::builder::NestedBuilder<derived_type,parent_type,result_type>(this, parent)
          ,AttributeTargetBuilder(this){
            begin();

        }
        template<typename Callable, typename ParentBuilder, size_t ArgIndex>
        ArgumentBuilder<Callable,ParentBuilder,ArgIndex>::ArgumentBuilder(parent_ptr parent, result_ptr result):
          core::builder::NestedBuilder<derived_type,parent_type,result_type>(parent,result),
          AttributeTargetBuilder(this,result)
        
        {

        }
        template<typename Callable, typename ParentBuilder, unsigned int ArgIndex>
        auto ArgumentBuilder<Callable,ParentBuilder,ArgIndex>::name(const std::string & n)->derived_ptr{
          result()->setName(n);
          return derived();
        }


      }
    }
  }
}
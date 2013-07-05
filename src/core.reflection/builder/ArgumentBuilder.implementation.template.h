#pragma once
#include "ArgumentBuilder.h"
#include <core.reflection/callable/ArgumentInfo.h>

#include <memory>
namespace nspace{
  namespace core{
    namespace reflection{
      namespace builder{
        template<typename T, typename Method, unsigned int ArgIndex>
        auto ArgumentBuilder<T,Method,ArgIndex>::createInstance()->result_ptr{
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
        template<typename T, typename Method, unsigned int ArgIndex>
        auto ArgumentBuilder<T,Method,ArgIndex>::defaultValue(Argument argument)->derived_ptr{
          result()->setDefaultValue(argument);
          return derived();
        }

        template<typename T, typename Method, unsigned int ArgIndex>
        ArgumentBuilder<T,Method,ArgIndex>::ArgumentBuilder(parent_ptr parent):
          core::builder::NestedBuilder<derived_type,parent_type,result_type>(this, parent){
            begin();

        }
        template<typename T, typename Method, unsigned int ArgIndex>
        ArgumentBuilder<T,Method,ArgIndex>::ArgumentBuilder(parent_ptr parent, result_ptr result):
          core::builder::NestedBuilder<derived_type,parent_type,result_type>(parent,result){

        }
        template<typename T, typename Method, unsigned int ArgIndex>
        auto ArgumentBuilder<T,Method,ArgIndex>::name(const std::string & n)->derived_ptr{
          result()->setName(n);
          return derived();
        }


      }
    }
  }
}
#pragma once
#include <core.builder/NestedBuilder.h>
#include <core.reflection/function/ArgumentInfo.h>
namespace nspace{
  namespace core{
    namespace reflection{
      namespace builder{
        template<typename T>
        class TypeBuilder;

        template<typename T, typename Method>
        class MethodBuilder;

        template<typename T, typename Method, unsigned int ArgIndex>
        class ArgumentBuilder : 
          public core::builder::NestedBuilder<ArgumentBuilder<T,Method,ArgIndex>,MethodBuilder<T,Method>,ArgumentInfo>{

        public:
          typedef typename function_traits<Method>::nested_template arg<ArgIndex>::type argument_type;
          result_ptr createInstance()override{
            return parent()->result()->argument(ArgIndex);
          }

          derived_ptr defaultValue(const argument_type & value){
            return defaultValue((Argument)value);
          }
          derived_ptr defaultValue(std::shared_ptr<argument_type> value){
            return defaultValue((Argument)value);
          }
          derived_ptr defaultValue(Argument argument){
            result()->setDefaultValue(argument);
            return derived();
          }

          ArgumentBuilder(parent_ptr parent):
            core::builder::NestedBuilder<derived_type,parent_type,result_type>(this, parent){
              begin();

          }
          ArgumentBuilder(parent_ptr parent, result_ptr result):
            core::builder::NestedBuilder<derived_type,parent_type,result_type>(parent,result){

          }
          derived_ptr name(const std::string & n){
            result()->setName(n);
            return derived();
          }

        };
      }
    }
  }
}
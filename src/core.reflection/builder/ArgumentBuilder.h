#pragma once
#include <core.builder/NestedBuilder.h>
#include <core/template/function_traits.h>
#include <memory>
namespace nspace{
  namespace core{
    namespace reflection{
      namespace builder{
        // forward declaration
        template<typename T> class TypeBuilder;
        template<typename T, typename Method> class MethodBuilder;        
        class ArgumentInfo;
        

        // 
        template<typename T, typename Method, unsigned int ArgIndex>
        class ArgumentBuilder : 
          public core::builder::NestedBuilder<ArgumentBuilder<T,Method,ArgIndex>,MethodBuilder<T,Method>,ArgumentInfo>{
        public:
//          typedef typename function_traits<Method>::nested_template arg<ArgIndex>::type argument_type;
         
          result_ptr createInstance()override;

          // sets the default value for the specified argument
    //      derived_ptr defaultValue(const argument_type & value);
          // sets the default value for the specified argument
  //        derived_ptr defaultValue(std::shared_ptr<argument_type> value);
          // sets the default value for the specified argument
          derived_ptr defaultValue(Argument argument);

          ArgumentBuilder(parent_ptr parent);
          ArgumentBuilder(parent_ptr parent, result_ptr result);

          
          // sets the arguments name
          derived_ptr name(const std::string & n);

        };
      }
    }
  }
}
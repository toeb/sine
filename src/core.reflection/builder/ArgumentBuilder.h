#pragma once
#include <core.builder/NestedBuilder.h>
#include <core/template/callable_traits.h>
#include <memory>
#include <core.reflection/builder/AttributeTargetBuilder.h>
namespace nspace{
        class ArgumentInfo;
  namespace core{
    namespace reflection{
      namespace builder{
        // forward declaration
        
        

        // 
        template<typename Callable, typename ParentBuilder, size_t ArgIndex>
        class ArgumentBuilder : 
          public virtual AttributeTargetBuilder<ArgumentBuilder<Callable,ParentBuilder,ArgIndex>,ArgumentInfo>,
          public virtual core::builder::NestedBuilder<ArgumentBuilder<Callable,ParentBuilder,ArgIndex>,ParentBuilder,ArgumentInfo>{
        public:
          using NestedBuilder::end;
          using AttributeTargetBuilder::result;
          using AttributeTargetBuilder::begin;
          using NestedBuilder::derived;
          result_ptr createInstance()override;

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
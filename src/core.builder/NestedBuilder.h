#pragma once
#include <core.builder/Builder.h>
namespace nspace{
  namespace core{
    namespace builder{
      /**
      * a nested builder has a parent builder which is returned via end()
      * and is accessible via parent()
      */
      template<typename Derived, typename ParentBuilder, typename ResultType>
      class NestedBuilder : public virtual Builder<Derived,ResultType>{
      public:
        typedef typename ParentBuilder * parent_ptr;
        typedef typename ParentBuilder parent_type;
      private:
        parent_ptr _parentBuilder;
      public:
        NestedBuilder(derived_ptr derived, parent_ptr parent):Builder(derived),_parentBuilder(parent){}
        NestedBuilder(derived_ptr derived, parent_ptr parent,result_ptr result):Builder(derived,result),_parentBuilder(parent){}

        parent_ptr parent(){
          return _parentBuilder;
        }
        
        parent_ptr end(){
          Builder<Derived,ResultType>::end();
          return _parentBuilder;
        }

      };
    }
  }
}
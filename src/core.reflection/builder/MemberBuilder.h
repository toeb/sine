#pragma once
#include <core.builder/NestedBuilder.h>
namespace nspace{
  enum AccessModifier;
  namespace core{
    namespace reflection{
      namespace builder{
        template<typename T> class TypeBuilder;

        template<typename Derived, typename T,typename MemberInfoType>
        class MemberBuilder        
          :public core::builder::NestedBuilder<Derived,TypeBuilder<T>,MemberInfoType>
        {
        protected:
          MemberBuilder(derived_ptr instance, parent_ptr parent, result_ptr memberInfo);
          MemberBuilder(derived_ptr instance, parent_ptr parent);
        public:
          // sets the accessmodified for the specified member
          derived_ptr accessModifier(AccessModifier modifier);
          // sets the name as well as the full name of a member
          virtual derived_ptr name(const std::string & name);
        };
      }
    }
  }
}
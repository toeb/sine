#pragma once

#include <core.builder/NestedBuilder.h>
#include <core.reflection/member/MemberInfo.h>
namespace nspace{
  namespace core{
    namespace reflection{
      namespace builder{
        
        template<typename T> class TypeBuilder;

        template<typename Derived, typename T,typename MemberInfoType>
        class MemberBuilder        
          :public core::builder::NestedBuilder<Derived,TypeBuilder<T>,MemberInfoType>
        {
        protected:
          MemberBuilder(derived_ptr instance, parent_ptr parent, result_ptr memberInfo)
            : NestedBuilder<derived_type,parent_type,result_type>(instance,parent,memberInfo){

          }
          MemberBuilder(derived_ptr instance, parent_ptr parent)
            : NestedBuilder<derived_type,parent_type,result_type>(instance,parent){

          }
        public:
          derived_ptr accessModifier(AccessModifier modifier){
            result()->setAccessModifier(modifier);
            return derived();
          }
          // sets the name as well as the full name of a member
          virtual derived_ptr name(const std::string & name){            
            result()->setName(name);
            result()->setFullName(name);
            return derived();
          }
        };
      }
    }
  }
}
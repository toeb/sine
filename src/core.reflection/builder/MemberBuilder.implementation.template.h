#pragma once
#include "MemberBuilder.h"

#include <core.reflection/builder/TypeBuilder.implementation.template.h>
#include <core.reflection/member/MemberInfo.h>
//#include <core.reflection/member/method/MethodInfo.h>
//#include <core.reflection/member/method/TypedMethodInfo.h>
namespace nspace{
  namespace core{
    namespace reflection{
      namespace builder{

        template<typename Derived, typename T,typename MemberInfoType>
        MemberBuilder<Derived,T,MemberInfoType>::MemberBuilder(derived_ptr instance, parent_ptr parent, result_ptr memberInfo)
          : NestedBuilder<derived_type,parent_type,result_type>(instance,parent,memberInfo){

        }
        template<typename Derived, typename T,typename MemberInfoType>
        MemberBuilder<Derived,T,MemberInfoType>::MemberBuilder(derived_ptr instance, parent_ptr parent)
          : NestedBuilder<derived_type,parent_type,result_type>(instance,parent){

        }
        template<typename Derived, typename T,typename MemberInfoType>
        auto MemberBuilder<Derived,T,MemberInfoType>::accessModifier(AccessModifier modifier)->derived_ptr{
          result()->setAccessModifier(modifier);
          return derived();
        }
        // sets the name as well as the full name of a member
        template<typename Derived, typename T,typename MemberInfoType>
        auto MemberBuilder<Derived,T,MemberInfoType>::name(const std::string & name)->derived_ptr{            
          result()->setName(name);
          result()->setFullName(name);
          return derived();
        }
      }
    }
  }
}
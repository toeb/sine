#pragma once

#include "MethodBuilder.h"
#include <core.reflection/builder/MemberBuilder.implementation.template.h>
#include <core.reflection/member/method/TypedMethodInfo.h>
#include <core.reflection/callable/ArgumentInfo.h>
#include <memory>
//#include <core.reflection/builder/ArgumentBuilder.h>

namespace nspace{
  namespace core{
    namespace reflection{
      namespace builder{

        template<typename T, typename Method>
        MethodBuilder<T,Method>::MethodBuilder(parent_ptr parentBuilder, Method method):
          MemberBuilder<MethodBuilder<T,Method>,T,MethodInfo>(this,parentBuilder),
          _method(method)
        {

        }
        // sets the name part of the signature / causes fullname and pure name as well as name to be set           
        template<typename T, typename Method>
        auto MethodBuilder<T,Method>::name(const std::string &purename) ->derived_ptr{
          std::stringstream nameStream, fullNameStream;
          nameStream<<purename<<"(";
          fullNameStream<<purename<<"(";

          for(auto it = result()->Arguments().begin(); it != result()->Arguments().end(); it++){
            auto arg  = *it;
            if(it != result()->Arguments().begin()){
              nameStream << ", ";
              fullNameStream <<", ";
            }
            nameStream << arg->getArgumentType()->getName();
            nameStream << arg->getArgumentType()->getFullyQualifiedName();
          }
          fullNameStream <<")";
          nameStream <<")";
          if(result()->getIsConst()){
            fullNameStream <<"const";
            nameStream <<"const";
          }
          auto name = nameStream.str();
          auto fullName = fullNameStream.str();
          result()->setName(name);
          result()->setFullName(name);
          result()->setPureName(purename);
          return derived();
        }
        
        template<typename T, typename Method>
        template<size_t ArgumentIndex>
        std::shared_ptr<ArgumentBuilder<Method,MethodBuilder<T,Method>, ArgumentIndex>> MethodBuilder<T,Method>::argument() {            
          auto result = std::make_shared<ArgumentBuilder<Method,derived_type,ArgumentIndex>>(this);
          result->begin();
          return result;            
        }

        
           


        template<typename T, typename Method>
        auto MethodBuilder<T,Method>::createInstance()->result_ptr{
          static auto info = method_info_shared(_method);
          return info;
        }

        template<typename T, typename Method>
        void MethodBuilder<T,Method>::onBeforeEnd(){
          parent()->result()->Members()|=result().get();
        }


      }
    }
  }
}
#pragma once

#include <core.builder/NestedBuilder.h>
#include <core.reflection/member/method/TypedMethodInfo.h>
#include <core.reflection/builder/MemberBuilder.h>
namespace nspace{
  namespace core{
    namespace reflection{
      namespace builder{

        template<typename T, typename Method>
        class MethodBuilder : 
          public MemberBuilder<MethodBuilder<T,Method>,T, MethodInfo>{
        private:
          Method _method;
        public:
          MethodBuilder(parent_ptr parentBuilder, Method method):
            MemberBuilder(this,parentBuilder),
            _method(method)
          {

          }
          // sets the name part of the signature / causes fullname and pure name as well as name to be set
          derived_ptr name(const std::string &purename) override{
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

          template<unsigned int ArgumentIndex>
          std::shared_ptr<ArgumentBuilder<T,Method,ArgumentIndex>> argument(){            
            auto result = std::make_shared<ArgumentBuilder<T,Method,ArgumentIndex>>(this);
            return result;            
          }


          result_ptr createInstance(){
            static std::shared_ptr<TypedMethodInfo<Method>> _instance = std::make_shared<TypedMethodInfo<Method>>(_method);
            return _instance;
          }

          void onBeforeEnd()override{
            parent()->result()->Members()|=result().get();
          }

        };
      }
    }
  }
}
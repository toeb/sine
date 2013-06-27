#pragma once

#include <core.builder/NestedBuilder.h>
#include <core.reflection/member/method/TypedMethodInfo.h>
namespace nspace{
  namespace core{
    namespace reflection{
      namespace builder{
        template<typename T> class TypeBuilder;
        template<typename T, typename Method>
        class MethodBuilder : 
          public core::builder::NestedBuilder<MethodBuilder<T,Method>,TypeBuilder<T>, MethodInfo>{
        private:
          Method _method;
        public:
          MethodBuilder(parent_ptr parentBuilder, Method method):
            core::builder::NestedBuilder<derived_type,parent_type,result_type>(this,parentBuilder),
            _method(method)
          {

          }
          derived_ptr name(const std::string &name){
            result()->setName(name);
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
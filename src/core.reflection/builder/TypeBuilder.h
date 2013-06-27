#pragma once
#include <core.reflection/builder/ScopeBuilder.h>
namespace nspace{






  namespace core{
    namespace reflection{
      namespace builder{

        template<typename T>
        std::shared_ptr<TypeBuilder<T>> reflect(){
          auto builder =std::make_shared<TypeBuilder<T>>();
          builder->begin();
          return builder;
        }
        template<typename T>
        class TypeBuilder :public ScopeBuilder<TypeBuilder<T>, Type> {
        protected:
          result_ptr createInstance()override{
            return TypeInfo<T>::instance();
          }
        public:
          TypeBuilder(result_ptr type):ScopeBuilder(this,type){

          }
          TypeBuilder():ScopeBuilder(this,result_ptr()){

          }

          template<typename Method>
          std::shared_ptr<MethodBuilder<T,Method>> method(Method method){
            auto builder = std::make_shared<MethodBuilder<T,Method>>(this,method);
            builder->begin();
            return builder;
          }
        };
      }
    }
  }
}
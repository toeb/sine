#pragma once
#include <core.reflection/builder/ScopeBuilder.h>
#include <core.reflection/builder/ConstructorBuilder.h>
#include <core.reflection/builder/MethodBuilder.h>
#include <core.reflection/member/constructor/ConstructorInfo.h>
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
          template<typename SuperType>
          derived_ptr supertype(){            
            auto type = TypeInfo<SuperType>::instance().get();
            result()->successors()|=type;
            throw new std::exception("not implemented");
            return derived();
          }

        private:
          template<typename ConstructorArgTuple>
          auto constructorBuilder()
            ->std::shared_ptr<ConstructorBuilder<T,TypedConstructorInfo<T,ConstructorArgTuple>>>
          {
            static auto constructorInfo  = std::make_shared<TypedConstructorInfo<T,ConstructorArgTuple>>();
            auto builder = std::make_shared<ConstructorBuilder<T,TypedConstructorInfo<T,ConstructorArgTuple>>>(this, constructorInfo);            
            builder->name("ctor");
            return builder;
          }
        public:


          auto constructor()->decltype(constructorBuilder<void>()){            
            return constructorBuilder<void>();
          }
          template<typename T0>
          auto constructor()->decltype(constructorBuilder<std::tuple<T0>>()){
            return constructorBuilder<std::tuple<T0>>();
          }

          template<typename T0,typename T1>
          auto constructor()->decltype(constructorBuilder<std::tuple<T0,T1>>()){
            return constructorBuilder<std::tuple<T0,T1>>();
          }

          template<typename T0,typename T1,typename T2>
          auto constructor()->decltype(constructorBuilder<std::tuple<T0,T1,T2>>()){
            return constructorBuilder<std::tuple<T0,T1,T2>>();
          }


          /// creates a method builder for the specified method address
          /// 
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
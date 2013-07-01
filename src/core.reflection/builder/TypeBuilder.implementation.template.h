#pragma once
#include "TypeBuilder.h"

//#include <core.reflection/builder/ConstructorBuilder.implementation.template.h>
#include <core.reflection/builder/MethodBuilder.h>
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
        auto TypeBuilder<T>::createInstance()->result_ptr{
          return TypeInfo<T>::instance();
        }
        template<typename T>
        TypeBuilder<T>::TypeBuilder(result_ptr type):ScopeBuilder(this,type){

        }
        template<typename T>
        TypeBuilder<T>::TypeBuilder():ScopeBuilder(this,result_ptr()){

        }
        template<typename T>
        template<typename SuperType>
        auto  TypeBuilder<T>::supertype()-> derived_ptr{            
          auto type = TypeInfo<SuperType>::instance().get();
          result()->successors()|=type;
          throw new std::exception("not implemented");
          return derived();
        }
        /*
        template<typename T>
        template<typename ConstructorArgTuple>
        auto  TypeBuilder<T>::constructorBuilder()
        ->std::shared_ptr<ConstructorBuilder<T,TypedConstructorInfo<T,ConstructorArgTuple>>>
        {
        static auto constructorInfo  = std::make_shared<TypedConstructorInfo<T,ConstructorArgTuple>>();
        auto builder = std::make_shared<ConstructorBuilder<T,TypedConstructorInfo<T,ConstructorArgTuple>>>(this, constructorInfo);            
        builder->name("ctor");
        return builder;
        }



        auto  TypeBuilder<T>::constructor()->decltype(constructorBuilder<void>()){            
        return constructorBuilder<void>();
        }
        template<typename T0>
        auto  TypeBuilder<T>::constructor()->decltype(constructorBuilder<std::tuple<T0>>()){
        return constructorBuilder<std::tuple<T0>>();
        }

        template<typename T0,typename T1>
        auto  TypeBuilder<T>::constructor()->decltype(constructorBuilder<std::tuple<T0,T1>>()){
        return constructorBuilder<std::tuple<T0,T1>>();
        }

        template<typename T0,typename T1,typename T2>
        auto  TypeBuilder<T>::constructor()->decltype(constructorBuilder<std::tuple<T0,T1,T2>>()){
        return constructorBuilder<std::tuple<T0,T1,T2>>();
        }
        */


        template<typename T>
        template<typename Method>
        std::shared_ptr<MethodBuilder<T,Method>> TypeBuilder<T>::method(Method method){
          auto builder = std::make_shared<MethodBuilder<T,Method>>(this,method);
          builder->begin();
          return builder;
        }


      }
    }
  }
}
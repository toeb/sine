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


        template<typename T>
        template<typename Method>
        std::shared_ptr<MethodBuilder<T,Method>> TypeBuilder<T>::method(Method method){
          auto builder = std::make_shared<MethodBuilder<T,Method>>(this,method);
          builder->begin();
          return builder;
        }

        template<typename Class>
        auto TypeBuilder<Class>::constructor()->std::shared_ptr<ConstructorBuilder<Class,TypedConstructorInfo<Class>>>{
          auto instance = std::make_shared<ConstructorBuilder<Class,TypedConstructorInfo<Class>>>(this);
          instance->begin();
          return instance;
        }; 

        template<typename Class>
        template<typename T0>
        auto TypeBuilder<Class>::constructor()->std::shared_ptr<ConstructorBuilder<Class,TypedConstructorInfo<Class, T0>>>{
          auto instance = std::make_shared<ConstructorBuilder<Class,TypedConstructorInfo<Class, T0>>>(this);
          instance->begin();
          return instance;
        }; 

        template<typename Class>
        template<typename T0, typename T1>
        auto TypeBuilder<Class>::constructor()->std::shared_ptr<ConstructorBuilder<Class,TypedConstructorInfo<Class, T0, T1>>>{
          auto instance = std::make_shared<ConstructorBuilder<Class,TypedConstructorInfo<Class, T0, T1>>>(this);          
          instance->begin();
          return instance;
        }; 

        template<typename Class>
        template<typename T0, typename T1, typename T2>
        auto TypeBuilder<Class>::constructor()->std::shared_ptr<ConstructorBuilder<Class,TypedConstructorInfo<Class, T0, T1, T2>>>{
          auto instance = std::make_shared<ConstructorBuilder<Class,TypedConstructorInfo<Class, T0, T1, T2>>>(this);
          instance->begin();
          return instance;
        }; 

        template<typename Class>
        template<typename T0, typename T1, typename T2, typename T3>
        auto TypeBuilder<Class>::constructor()->std::shared_ptr<ConstructorBuilder<Class,TypedConstructorInfo<Class, T0, T1, T2, T3>>>{
          auto instance = std::make_shared<ConstructorBuilder<Class,TypedConstructorInfo<Class, T0, T1, T2, T3>>>(this);
          instance->begin();
          return instance;
        }; 

        template<typename Class>
        template<typename T0, typename T1, typename T2, typename T3, typename T4>
        auto TypeBuilder<Class>::constructor()->std::shared_ptr<ConstructorBuilder<Class,TypedConstructorInfo<Class, T0, T1, T2, T3, T4>>>{
          auto instance = std::make_shared<ConstructorBuilder<Class,TypedConstructorInfo<Class, T0, T1, T2, T3, T4>>>(this);
          instance->begin();
          return instance;
        }; 

        template<typename Class>
        template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
        auto TypeBuilder<Class>::constructor()->std::shared_ptr<ConstructorBuilder<Class,TypedConstructorInfo<Class, T0, T1, T2, T3, T4, T5>>>{
          auto instance = std::make_shared<ConstructorBuilder<Class,TypedConstructorInfo<Class, T0, T1, T2, T3, T4, T5>>>(this);
          instance->begin();
          return instance;
        }; 

        template<typename Class>
        template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
        auto TypeBuilder<Class>::constructor()->std::shared_ptr<ConstructorBuilder<Class,TypedConstructorInfo<Class, T0, T1, T2, T3, T4, T5, T6>>>{
          auto instance = std::make_shared<ConstructorBuilder<Class,TypedConstructorInfo<Class, T0, T1, T2, T3, T4, T5, T6>>>(this);
          instance->begin();
          return instance;
        }; 

        template<typename Class>
        template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
        auto TypeBuilder<Class>::constructor()->std::shared_ptr<ConstructorBuilder<Class,TypedConstructorInfo<Class, T0, T1, T2, T3, T4, T5, T6, T7>>>{
          auto instance = std::make_shared<ConstructorBuilder<Class,TypedConstructorInfo<Class, T0, T1, T2, T3, T4, T5, T6, T7>>>(this);
          instance->begin();
          return instance;
        }; 

        template<typename Class>
        template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
        auto TypeBuilder<Class>::constructor()->std::shared_ptr<ConstructorBuilder<Class,TypedConstructorInfo<Class, T0, T1, T2, T3, T4, T5, T6, T7, T8>>>{
          auto instance = std::make_shared<ConstructorBuilder<Class,TypedConstructorInfo<Class, T0, T1, T2, T3, T4, T5, T6, T7, T8>>>(this);
          instance->begin();
          return instance;
        }; 


      }
    }
  }
}
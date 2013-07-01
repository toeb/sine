#pragma once
#include <core.reflection/builder/ScopeBuilder.h>
namespace nspace{
  namespace core{
    namespace reflection{
      namespace builder{
        template<typename T, typename Method> class MethodBuilder;
        template<typename T> class TypeBuilder;
        // returns a type builder for the type specified by T
        template<typename T> std::shared_ptr<TypeBuilder<T>> reflect();

        template<typename T>
        class TypeBuilder :public ScopeBuilder<TypeBuilder<T>, Type> {
        protected:
          result_ptr createInstance()override;
        public:
          TypeBuilder(result_ptr type);
          TypeBuilder();
          template<typename SuperType>
          derived_ptr supertype();

          /*  
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
          */
        public:
          /// creates a method builder for the specified method address
          /// 
          template<typename Method>
          std::shared_ptr<MethodBuilder<T,Method>> method(Method method);

        };
      }
    }
  }
}
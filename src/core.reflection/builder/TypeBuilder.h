#pragma once
#include <core.reflection/builder/ScopeBuilder.h>
#include <core.reflection/builder/ConstructorBuilder.h>
#include <core.reflection/member/constructor/TypedConstructorInfo.h>
namespace nspace{
  namespace core{
    namespace reflection{
      namespace builder{

        template<typename Class, typename Method> class MethodBuilder;
        template<typename Class> class TypeBuilder;
        // returns a type builder for the type specified by T
        template<typename Class> std::shared_ptr<TypeBuilder<Class>> reflect();

        template<typename Class>
        class TypeBuilder :public ScopeBuilder<TypeBuilder<Class>, Type> {
        protected:
          result_ptr createInstance()override;
        public:
          TypeBuilder(result_ptr type);
          TypeBuilder();
          template<typename SuperType>
          derived_ptr supertype();

        public:


          // overloads for constructor builders
          auto constructor()->std::shared_ptr<ConstructorBuilder<Class,TypedConstructorInfo<Class>>>;
          template<typename T0>
          auto constructor()->std::shared_ptr<ConstructorBuilder<Class,TypedConstructorInfo<Class, T0>>>;
          template<typename T0, typename T1>
          auto constructor()->std::shared_ptr<ConstructorBuilder<Class,TypedConstructorInfo<Class, T0, T1>>>;
          template<typename T0, typename T1, typename T2>
          auto constructor()->std::shared_ptr<ConstructorBuilder<Class,TypedConstructorInfo<Class, T0, T1, T2>>>;
          template<typename T0, typename T1, typename T2, typename T3>
          auto constructor()->std::shared_ptr<ConstructorBuilder<Class,TypedConstructorInfo<Class, T0, T1, T2, T3>>>;
          template<typename T0, typename T1, typename T2, typename T3, typename T4>
          auto constructor()->std::shared_ptr<ConstructorBuilder<Class,TypedConstructorInfo<Class, T0, T1, T2, T3, T4>>>;
          template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
          auto constructor()->std::shared_ptr<ConstructorBuilder<Class,TypedConstructorInfo<Class, T0, T1, T2, T3, T4, T5>>>;
          template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
          auto constructor()->std::shared_ptr<ConstructorBuilder<Class,TypedConstructorInfo<Class, T0, T1, T2, T3, T4, T5, T6>>>;
          template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
          auto constructor()->std::shared_ptr<ConstructorBuilder<Class,TypedConstructorInfo<Class, T0, T1, T2, T3, T4, T5, T6, T7>>>;
          template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
          auto constructor()->std::shared_ptr<ConstructorBuilder<Class,TypedConstructorInfo<Class, T0, T1, T2, T3, T4, T5, T6, T7, T8>>>;



        public:
          /// creates a method builder for the specified method address
          /// 
          template<typename Method>
          std::shared_ptr<MethodBuilder<Class,Method>> method(Method method);

        };
      }
    }
  }
}
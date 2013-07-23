#pragma once
#include <core.reflection/builder/ScopeBuilder.h>
#include <core.reflection/builder/ConstructorBuilder.h>
#include <core.reflection/member/constructor/TypedConstructorInfo.h>
/**
* \addtogroup nspace::core::reflection::builder
*  Contains different builders for reflection
* 
*  a complete example using builders for reflection:
*  \snippet uninvasive.cpp reflect complete class
*/
namespace nspace{
  namespace core{
    namespace reflection{
      namespace builder{
        // forward declaration
        template<typename Class, typename Method> class MethodBuilder;
        template<typename Class> class TypeBuilder;

        /**
        *  allows builder based reflection of a type T.
        *  this is the entrypoint for reflecting a class/structs members 
        *
        *  examples:
        *  \snippet uninvasive.cpp  reflect complete class
        */
        template<typename Class> std::shared_ptr<TypeBuilder<Class>> reflect();
               

        /**
        *  the TypeBuilder helps to reflect a type
        *  it allows reflection of
        *  - the types name
        *  - constructors
        *  - methods
        *  - (not yet) fields
        *  - (not yet properties)
        * 
        * examples: 
        *  \snippet test.core.reflection/uninvasive.cpp simple reflection
        */
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


          /**
          * reflects a constructor with (currently up to 8 arguments)
          * see also the overloads for multiple arguments (in future these methods might be replaced by variable template args)
          * 
          * examples:
          * - \snippet univasive.cpp reflect default constructor
          * - \snippet univasive.cpp reflect overloaded constructor
          */
          auto constructor()->std::shared_ptr<ConstructorBuilder<Class,TypedConstructorInfo<Class>>>;
          /**
          * 
          */
          template<typename T0>
          auto constructor()->std::shared_ptr<ConstructorBuilder<Class,TypedConstructorInfo<Class, T0>>>;
          template<typename T0, typename T1>
          /*! @copydoc TypeBuilder<T>::constructor()
          * reflects a constructor with a single argument
          */
          auto constructor()->std::shared_ptr<ConstructorBuilder<Class,TypedConstructorInfo<Class, T0, T1>>>;
          template<typename T0, typename T1, typename T2>
         /*! @copydoc TypeBuilder<T>::constructor()
          * reflects a constructor with 2 arguments
          */
          auto constructor()->std::shared_ptr<ConstructorBuilder<Class,TypedConstructorInfo<Class, T0, T1, T2>>>;
          template<typename T0, typename T1, typename T2, typename T3>
         /*! @copydoc TypeBuilder<T>::constructor()
          * reflects a constructor with three argument
          */
          auto constructor()->std::shared_ptr<ConstructorBuilder<Class,TypedConstructorInfo<Class, T0, T1, T2, T3>>>;
         /*! @copydoc TypeBuilder<T>::constructor()
          * reflects a constructor with four argument
          */
          template<typename T0, typename T1, typename T2, typename T3, typename T4>
          auto constructor()->std::shared_ptr<ConstructorBuilder<Class,TypedConstructorInfo<Class, T0, T1, T2, T3, T4>>>;
          /**
          * \see constructor()
          */
          template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
          auto constructor()->std::shared_ptr<ConstructorBuilder<Class,TypedConstructorInfo<Class, T0, T1, T2, T3, T4, T5>>>;
          /**
          * \see constructor()
          */
          template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
          auto constructor()->std::shared_ptr<ConstructorBuilder<Class,TypedConstructorInfo<Class, T0, T1, T2, T3, T4, T5, T6>>>;
          /**
          * \see constructor()
          */
          template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
          auto constructor()->std::shared_ptr<ConstructorBuilder<Class,TypedConstructorInfo<Class, T0, T1, T2, T3, T4, T5, T6, T7>>>;
          /**
          * \see constructor()
          */
          template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
          auto constructor()->std::shared_ptr<ConstructorBuilder<Class,TypedConstructorInfo<Class, T0, T1, T2, T3, T4, T5, T6, T7, T8>>>;



        public:
          /**
          * reflects a specific method 
          * to disambiguate overloaded functions  \see{ signature, const_signature, static_signature }
          * examples:
          *  \snippet uninvasive.cpp reflect overloaded method
          */
          template<typename Method>
          std::shared_ptr<MethodBuilder<Class,Method>> method(Method method);
          

        };
      }
    }
  }
}
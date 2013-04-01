#pragma once

#include <core/patterns/Singleton.h>
#include <core.reflection/preprocessor/type.h>
#include <sstream>
#include <core.reflection/type/Type.h>
namespace nspace{

  template<typename T, bool hasDefaultConstructor = std::is_default_constructible<T>::value && !std::is_abstract<T>::value>
  struct add_default_constructor{
    static void add(void * type){}
  };

  template<typename T>
  class TraitType : public Type{
    typedef T type;
  protected:
    TraitType(const std::string & fullyQualifiedName, const Type * underlyingType=0):Type(fullyQualifiedName,underlyingType){init();}
  private:
    // friend class add_default_constructor<T>;
    void init(){
      add_default_constructor<T>::add(this);
    }
  };



  /**
  * \brief Information about the type.
  *        assumes T has method getTypeName which returns the fully qualified type name
  */
  template<typename T>
  class TypeInfo : public TraitType<T>
  {
    typedef typename std::remove_pointer<T>::type pureType;
    DS_SINGLETON_TEMPLATED(TypeInfo, T) :TraitType(pureType::getTypeName(),this){     
    }
  };

  template<typename T> const Type * type_of();
  template<typename T> const Type * type_of(const T & t);
  template<typename SuperType, typename TestType> bool subclassof();
  template<typename SuperType, typename TestType> bool subclassof(const TestType & b);
  template<typename SuperType, typename TestType> bool subclassof(const SuperType & a, const TestType & b);



}

// template implemetation

namespace nspace{

  template<typename T> const Type * type_of(){
    return nspace::TypeInfo<T>::instance().get();
  }

  template<typename T> const Type * type_of(const T & t){
    return type_of<T>();
  }

  template<typename SuperType, typename TestType> bool subclassof(){
    const Type * t1 = type_of<SuperType>();
    const Type * t2 = type_of<TestType>();
    return t2->isSubClassOf(t1);
  }



  template<typename SuperType, typename TestType> bool subclassof(const TestType & b){
    return subclassof<SuperType,TestType>();
  }
  template<typename SuperType, typename TestType> bool subclassof(const SuperType & a, const TestType & b){
    return subclassof<SuperType,TestType>();  
  }

}


// specialization for nspace::Set
#include <core.collection/containers/Set.h>
namespace nspace{
  /**
  * \brief Information about the type. Set<T>  /specialization
  *
  * \tparam  T Generic type parameter.
  */
  template<typename T>
  class TypeInfo<Set<T> >: public TraitType<Set<T> >
  {
    TEMPLATEDSINGLETON(TypeInfo, Set<T>):TraitType(DS_INLINE_STRING("Set<"<< typeof(T)<<">"),0) {
    }
  };
}

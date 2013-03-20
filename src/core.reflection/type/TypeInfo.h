#pragma once

#include <core.reflection/type/Type.h>
#include <core/patterns/Singleton.h>
#include <sstream>
#include <core.reflection/preprocessor/type.h>
namespace nspace{
  template<typename T>
  class TraitType : public Type{
  protected:
    TraitType(const std::string & fullyQualifiedName, const Type * underlyingType):Type(fullyQualifiedName,underlyingType){}
    TraitType(){
    }
  };

  /**
  * \brief Information about the type.
  */
  template<typename T>
  class TypeInfo : public TraitType<T>
  {
    DS_SINGLETON_TEMPLATED(TypeInfo, T) {
      typedef typename std::remove_pointer<T>::type pureType;
      setName(pureType::getTypeName());      
      setRawType(this);
      setUnderlyingType(0);
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
  TEMPLATEDSINGLETON(TypeInfo, Set<T>) {
    setName(DS_INLINE_STRING("Set<"<< typeof(T)<<">"));
  }
};
}

// specializations

#include <core.reflection/type/specialization/fundementalTypes.h>
#include <core.reflection/type/specialization/qualifierTypes.h>
#include <core.reflection/type/specialization/stdTypes.h>


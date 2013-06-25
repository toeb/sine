#pragma once

#include <core/patterns/Singleton.h>
#include <core.reflection/preprocessor/type.h>
#include <sstream>
#include <core.reflection/type/Type.h>
namespace nspace{
  /*

  template<typename T>
  class TraitType : public Type{
    typedef T type;
  protected:
    TraitType(const std::string & name);
  private:
    void init();
  };
  template<typename T1=std::_Nil,typename T2=std::_Nil,typename T3=std::_Nil,typename T4=std::_Nil,typename T5=std::_Nil,typename T6=std::_Nil>
  struct TypeTemplateArguments{
    TypeTemplateArguments(Type * type){
      type->setIsTemplated(false);
    }
  };
  template<typename T1>
  struct TypeTemplateArguments<T1,std::_Nil,std::_Nil,std::_Nil,std::_Nil,std::_Nil>{
    TypeTemplateArguments(Type * type){
      type->setIsTemplated(true);
      type->TemplateArguments().push_back(type_of<T1>());
    }
  };
  template<typename T1,typename T2>
  struct TypeTemplateArguments<T1,T2,std::_Nil,std::_Nil,std::_Nil,std::_Nil>{
    TypeTemplateArguments(Type * type){
      type->setIsTemplated(true);
      type->TemplateArguments().push_back(type_of<T1>());
      type->TemplateArguments().push_back(type_of<T2>());
    }
  };
  template<typename T1,typename T2,typename T3>
  struct TypeTemplateArguments<T1,T2,T3,std::_Nil,std::_Nil,std::_Nil>{
    TypeTemplateArguments(Type * type){
      type->setIsTemplated(true);
      type->TemplateArguments().push_back(type_of<T1>());
      type->TemplateArguments().push_back(type_of<T2>());
      type->TemplateArguments().push_back(type_of<T3>());
    }
  };

  */

  /**
  * \brief Information about the type.
  *        assumes T has method getTypeName which returns the fully qualified type name
  */
  template<typename T>
  class TypeInfo
  {
  public:
    static std::shared_ptr<Type> instance(){
      static std::shared_ptr<Type> _instance = std::make_shared<Type>();
      return _instance;
    };
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

/*
// specialization for nspace::Set
#include <core.collection/containers/Set.h>
namespace nspace{
  template<typename T>
  class TypeInfo<Set<T> >: public TraitType<Set<T> >
  {
    TEMPLATEDSINGLETON(TypeInfo, Set<T>):TraitType(DS_INLINE_STRING("Set<"<< typeof(T)<<">"),0) {
    }
  };
}
*/
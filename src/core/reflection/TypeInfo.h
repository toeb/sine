#pragma once

#include <core/reflection/Type.h>
#include <core/patterns/Singleton.h>
#include <core/template/default_constructor.h>


#define DS_META_TYPENAME(TYPE) template<> struct meta_type_name<TYPE>{static const std::string & value(){static std::string name = #TYPE; return name;}};
#define DS_META_INSTANCIATE_DEFAULT_CONSTRUCTOR(TYPE) template<> struct meta_type_construction<TYPE> { static const bool constructible = true; static std::shared_ptr<void> construct(){return std::shared_ptr<void>(new TYPE());}};
#define DS_META_TOSTRING(TYPE) template<> struct meta_type_tostring<TYPE>{ static void toString(const void * object, std::ostream & stream){if(!object)return; stream << *static_cast<const TYPE*>(object);}};



#define DS_META_TRIVIAL_TYPE(TYPE)DS_META_TYPENAME(TYPE) DS_META_INSTANCIATE_DEFAULT_CONSTRUCTOR(TYPE) DS_META_TOSTRING(TYPE)

/**
* \brief macro which allows typeinfo to be declared for any type  (which is not part of the nspace::Object  hierachy)
*        specializes the setupTypeInfo method and just sets the type name
*
* \param TYPE  The type.
*/
#define META(TYPE) DS_META_TYPENAME(TYPE);



/**
* \brief this macro returns the Type * instance for TYPENAME.
*
* \param TYPENAME  The typename.
*/
#define typeof(TYPENAME) nspace::TypeInfo<TYPENAME>::instance().get()


/**
* \brief Macro for making an object a typed object. defines a static meta information structure
*        (TypeData) and virtual access methods 
*
* \param TYPE  The type.
*/
#define DS_CLASS(TYPE)                                                                                                \
private:                                                                                                              \
  typedef TYPE CurrentClassType;                                                                                      \
public:                                                                                                               \
  static std::string getTypeName(){return std::string(# TYPE); }                                                      \
  virtual inline const nspace::Type & getType() const {return *nspace::TypeInfo<CurrentClassType>::instance(); }      \
  virtual inline bool isInstanceOf(const nspace::Type * type) const { return type->isSuperClassOf(this->getType()); } \
private:

#define TYPED_OBJECT(TYPE) DS_CLASS(TYPE)

/**
* \brief sets up inheritance hierarchy.
*        Subclass specify SUBCLASSOF in the class declaration so that the hierarchy can be generated
*
* \param TYPE  The parent type.
*/
#define SUBCLASSOF(TYPE)                                                                                                \
private:                                                                                                                \
  STATIC_INITIALIZER(TYPE ## Subclass,{                                                                                 \
  auto unconstCurrentType = const_cast<nspace::Type*>(dynamic_cast<const nspace::Type*>(typeof(CurrentClassType)));   \
  auto unconstSuperType = const_cast<nspace::Type*>(dynamic_cast<const nspace::Type*>(typeof(TYPE)));                 \
  unconstSuperType->successors()|=unconstCurrentType;                                                                 \
  })




namespace nspace{

  template<typename T>
  struct meta_type_name{
    static const std::string & value(){
      static std::string name = T::getTypeName();
      return name;
    }
  };
  template<typename T>
  struct meta_type_construction{
    static const bool constructible = default_constructor<T>::isConstructible;
    static std::shared_ptr<void> construct(){
      return default_constructor<T>::construct();
       //return std::shared_ptr<void>();
    }
  };
  template<typename T>
  struct meta_type_tostring{
    static void toString(const void * object, std::ostream& stream){
      stream <<static_cast<const T*>(object);
    }
  };
  /*
  template<typename T, bool ispointer = std::is_pointer<T>::value, bool isreference=std::is_reference<T>::value, bool isconst=std::is_const<T>::value>
  struct underlying_type{
    typedef T type;
  };


  template<typename T, bool ispointer, bool isreference, bool isconst>
  struct underlying_type{
    typedef T type;
  };


  */
  /**
  * \brief Information about the type.
  */
  template<typename T>
  class TypeInfo : public Type
  {     
  public:
    typedef typename std::remove_const<typename std::remove_pointer<T>::type>::type type;

    TEMPLATEDSINGLETON(TypeInfo, <T>) {
      setName(getTypeName());
      setIsConstructible(meta_type_construction<type>::constructible);
      if(getIsConstructible()){
        setCreateInstanceFunction([](){return createInstanceOfType();});
      }
      setObjectToStringFunction([](const void * object, std::ostream & stream){toString(object,stream);});
      

    }
  public:
    
    static const std::string & getTypeName(){
      return meta_type_name<type>::value();
    }

  
    static std::shared_ptr<void> createInstanceOfType(){    
      return meta_type_construction<type>::construct();
    }

    static void toString(const void * object, std::ostream & stream){      
      meta_type_tostring<type>::toString(object,stream);
    }



  };


}

/*
template<typename T>
struct getTypeNameImpl{
static const  std::string & getTypeName(){
static std::string name = T::getTypeName();
return name;
}
};


template<typename T> std::string typeNameOf( ){
return getTypeNameImpl<T>::getTypeName();
}*/
#pragma once


  /**
  * \brief this macro returns the Type * instance for TYPENAME.
  *
  * \param TYPENAME  The typename.
  */
#define typeof(TYPENAME) nspace::type_of<TYPENAME>()


  /**
  * \brief macro allows typeinfo to be declared for primitve types. or external types
  *
  * \param TYPE  The type.
  */
#define META(TYPE)                                                     \
  template<>                                                           \
  class TypeInfo<TYPE>: public TraitType<TYPE> {        \
  TEMPLATEDSINGLETON(TypeInfo, TYPE):TraitType(#TYPE){                              \
                                                   \
  }                                                                  \
  };

  /**
  * \brief META which set allows instancecreation of type by default constructor
  *
  * \param TYPE  The type.
  */
#define META_DEFAULTCONSTRUCTOR(TYPE) META(TYPE)



  /**
  * \brief Macro for making an object a typed object. defines a static meta information structure
  *        (TypeData) and virtual access methods
  * \param TYPE  The type.
  */
#define DS_CLASS(TYPE)                                                                                                \
private:                                                                                                              \
  typedef TYPE CurrentClassType;                                                                                      \
public:                                                                                                               \
  static const std::string & getTypeName(){static std::string name(#TYPE); return name; }                                                      \
  virtual inline const nspace::Type * getType() const {return nspace::TypeInfo<CurrentClassType>::instance().get(); } \
  virtual inline bool isInstanceOf(const nspace::Type * &  type) const { return type->isSuperClassOf(this->getType()); }         \
private:

#define TYPED_OBJECT(TYPE) DS_CLASS(TYPE)

#ifndef reflect_type
#define reflect_type(NAME) DS_CLASS(NAME) DS_PROPERTY_EXTENSION_METHODS 
#endif

#define reflect_superclasses(...) DS_FOREACH(SUBCLASSOF,__VA_ARGS__);

#define DS_CLASS_DECLARATION(TYPE)                                  \
private:                                                            \
  typedef TYPE CurrentClassType;                                    \
public:                                                             \
  static const std::string & getTypeName();                                 \
  virtual const nspace::Type * getType() const;              \
  virtual bool isInstanceOf(const Type * type) const;\
private:

#define DS_CLASS_DEFINITION(TYPE)                                                                                       \
  const std::string & TYPE::getTypeName(){static std::string name(# TYPE);return name; }                                                         \
  const nspace::Type * TYPE::getType() const {return nspace::TypeInfo<CurrentClassType>::instance().get(); }            \
  bool TYPE::isInstanceOf(const nspace::Type * type) const { return type->isSuperClassOf(this->getType()); }



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

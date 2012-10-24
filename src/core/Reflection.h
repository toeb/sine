#pragma once

#include <core/Property.h>
#include <core/TypedProperty.h>
#include <core/PropertyChangingObject.h>
#include <core/patterns/Singleton.h>



// to use reflection REFLECTABLE(<CLASSNAME>) needs to be 
// stated once in the class. it creates multiple things:
// - properties() : a static set of const Propert * which contains all reflectable properties of a class
// - getProperty(string) : a static method for accessing a property
// - T getPropertyValue(string name) : a class member which returns the value of the specified property
// - setPropertyValue(string name) : a class member for setting the value of a specific property
// - (a private set of const properties called propertiesSet())
// WARNING:  Since Class Hierarchy is not yet supported it is not possible to reflect upon properties of supertypes
// 
// after REFLECTABLE(<CLASSNAME>) was called you may add reflectable properties by
// adding :
// - REFLECTABLE_CUSTOM_PROPERTY
// - REFLECTABLE_PROPERTY
// - REFLECTABLE_NOTIFYING_PROPERTY
#define REFLECTABLE(TYPENAME)\
  typedef TYPENAME ReflectableType;\
  private:\
  static Set<const Property*> & propertiesSet(){\
  static Set<const Property*> * _propertiesSet=0;\
    if(!_propertiesSet){\
    _propertiesSet = new Set<const Property*>();\
    const TypeData & type = ClassType();\
    TypeData* unconstType= const_cast<TypeData*>(&type);\
    unconstType->properties =_propertiesSet;\
    }\
  return *_propertiesSet;\
  };\
  public:\
  template<typename T>\
  T getPropertyValue(const std::string & propertyname)const{T val; getPropertyValue(propertyname,val);return val;}\
  template<typename T>\
  void getPropertyValue(const std::string & propertyname,T & value)const{\
  auto prop = getProperty(propertyname);\
  if(!prop)return;\
  prop->get(value,*this);\
  }\
  template<typename T>\
  void setPropertyValue(const std::string & propertyname,const T & value){\
  auto prop = getProperty(propertyname);\
  if(!prop)return;\
  prop->set(value,*this);\
  }\
  static const Set<const Property*> &properties(){\
  return propertiesSet();\
  }\
  static const Property * getProperty(const std::string & propertyname){\
  auto p = properties().first([&propertyname](const Property * p ){return p->PropertyName()==propertyname;});\
  return p;\
  }\
  PropertyAdapter getPropertyAdapter(const std::string & name){\
    return PropertyAdapter(this,*getProperty(name));\
  }\
  private:\


// shorthand for a typed object which is also reflectable
#define REFLECTABLE_OBJECT(TYPE) TYPED_OBJECT(TYPE); REFLECTABLE(TYPE);

#define PROPERTYCLASS(NAME) NAME##PropertyClass

#define PROPERTYCLASSINSTANCE(NAME) ( (PROPERTYCLASS(NAME) * ) PROPERTYCLASS(NAME)::instance())

#define REFLECTABLE_CUSTOM_PROPERTY(TYPE,NAME,PROPERTYDECLARATION)\
  private:\
  class PROPERTYCLASS(NAME) : public virtual TypedProperty<ReflectableType,TYPE>{\
  TYPED_OBJECT( PROPERTYCLASS(NAME) );\
  public:\
  SINGLETON( PROPERTYCLASS(NAME) ){setPropertyName(#NAME);}\
  void setTypedValue(ReflectableType *  object , TYPE value)const{ object->set##NAME(value); }\
  TYPE getTypedValue(const ReflectableType *  object)const{ return object->get##NAME(); }\
  };\
  private:\
  STATIC_INITIALIZER(NAME##Property, { ReflectableType::propertiesSet() |= PROPERTYCLASSINSTANCE(NAME);})\
  PROPERTYDECLARATION(TYPE,NAME)

// sets the propertydisplayname property of the property object created for the property specified by NAME (.... property)
#define DISPLAYNAME(NAME, DNAME)\
  STATIC_INITIALIZER(NAME##DisplayName, {PROPERTYCLASSINSTANCE(NAME)->setPropertyDisplayName(DNAME);})

// sets the description of property specified by name
#define DESCRIPTION(NAME, DDESCRIPTION)\
  STATIC_INITIALIZER(NAME##Description, {PROPERTYCLASSINSTANCE(NAME)->setPropertyDescription(DDESCRIPTION);})

// sets the default value for the property specified by NAME  (make sure the type is correct) also add the set to default method
#define DEFAULTVALUE(NAME,DEFAULTVALUE)\
  public:\
  void set##NAME##ToDefault(){PROPERTYCLASSINSTANCE(NAME)->setToDefaultValue(this);}\
private:\
  STATIC_INITIALIZER(NAME##DefaultValue, {static auto defaultvalue = DEFAULTVALUE; PROPERTYCLASSINSTANCE(NAME)->setDefaultValue(&defaultvalue);})

// sets the groupname of the property specified by NAME
#define GROUPNAME(NAME,GROUP)\
  STATIC_INITIALIZER(NAME##GroupName,PROPERTYCLASSINSTANCE(NAME)->setGroupName(GROUP))

#define REFLECTABLE_PROPERTY(TYPE,NAME) REFLECTABLE_CUSTOM_PROPERTY(TYPE,NAME,SIMPLE_PROPERTY)
#define REFLECTABLE_NOTIFYING_PROPERTY(TYPE,NAME) REFLECTABLE_CUSTOM_PROPERTY(TYPE,NAME,NOTIFYING_PROPERTY)

// default property macro 
#define PROPERTY(TYPE,NAME) REFLECTABLE_NOTIFYING_PROPERTY(TYPE,NAME)

// creates a property for any nonpointer / nonreference field and addutionally allows access by reference
#define REF_PROP(TYPE,NAME) REFERENCE_PROPERTY(TYPE,NAME); PROPERTY(TYPE,NAME)



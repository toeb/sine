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
  static Set<const Property*> * _propertiesSet=new Set<const Property*>();\
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
  auto p = properties().first([&propertyname](const Property * p ){return p->propertyName()==propertyname;});\
  return p;\
  }\
  private:\


// shorthand for a typed object which is also reflectable
#define REFLECTABLE_OBJECT(TYPE) TYPED_OBJECT(TYPE); REFLECTABLE(TYPE);

#define REFLECTABLE_CUSTOM_PROPERTY(TYPE,NAME,PROPERTYDECLARATION)\
  public:\
  class NAME##PropertyClass : public virtual TypedProperty<ReflectableType,TYPE>{\
  TYPED_OBJECT(NAME##PropertyClass);\
  static NAME##PropertyClass * _instance;\
  public:\
  SINGLETON(NAME##PropertyClass){setPropertyName(#NAME);}\
  void setTypedValue(ReflectableType *  object , TYPE value)const{object->set##NAME(value); }\
  TYPE getTypedValue(const ReflectableType *  object)const{ return object->get##NAME(); }\
  };\
  private:\
  class __init##NAME##Class{\
  public:\
  __init##NAME##Class(){\
  ReflectableType::propertiesSet() |= NAME##PropertyClass::instance();\
  }\
  };\
  __init##NAME##Class __init##NAME;\
  PROPERTYDECLARATION(TYPE,NAME)

#define REFLECTABLE_PROPERTY(TYPE,NAME) REFLECTABLE_CUSTOM_PROPERTY(TYPE,NAME,SIMPLE_PROPERTY)
#define REFLECTABLE_NOTIFYING_PROPERTY(TYPE,NAME) REFLECTABLE_CUSTOM_PROPERTY(TYPE,NAME,NOTIFYING_PROPERTY)

// default property macro 
#define PROPERTY(TYPE,NAME) REFLECTABLE_NOTIFYING_PROPERTY(TYPE,NAME)

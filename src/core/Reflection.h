#pragma once

#include <core/Property.h>
#include <core/TypedProperty.h>
#include <core/PropertyChangingObject.h>
#include <core/patterns/Singleton.h>


#define REFLECTABLE_OBJECT(TYPENAME)\
  TYPED_OBJECT(TYPENAME);\
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

#define REFLECTABLE_PROPERTY(TYPE,NAME) REFLECTABLE_CUSTOM_PROPERTY(TYPE,NAME,PROPERTY)
#define REFLECTABLE_NOTIFYING_PROPERTY(TYPE,NAME) REFLECTABLE_CUSTOM_PROPERTY(TYPE,NAME,NOTIFYING_PROPERTY)
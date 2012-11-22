#pragma once

#include <core/reflection/PropertyInfo.h>
#include <core/reflection/MethodInfo.h>
#include <core/reflection/TypedProperty.h>
#include <core/reflection/TypedPropertySetInfo.h>
#include <core/reflection/PropertyAdapter.h>
#include <core/reflection/MethodAdapter.h>
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
  public:\
  template<typename T>\
  T getPropertyValue(const std::string & propertyname)const{\
    T val;\
    getPropertyValue(propertyname,val);\
    return val;\
  }\
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
  static const nspace::Set<const nspace::PropertyInfo*> & properties(){\
  static nspace::Set<const nspace::PropertyInfo*> _properties = typeof(TYPENAME)->Properties();\
    return _properties;\
  }\
  static const nspace::PropertyInfo * getProperty(const std::string & propertyname){\
    auto p = typeof(TYPENAME)->getProperty(propertyname);\
    return p;\
  }\
  nspace::PropertyAdapter getPropertyAdapter(const std::string & name){\
    return nspace::PropertyAdapter(dynamic_cast<nspace::Object*>(this),name);\
  }\
  nspace::MethodAdapter getMethodAdapter(const std::string & name){\
    return nspace::MethodAdapter(dynamic_cast<nspace::Object*>(this),name);\
  }\
  static const nspace::MethodInfo * getMethodInfo(const std::string & methodName){\
    return typeof(TYPENAME)->getMethodInfo(methodName);\
  }\
  private:




// shorthand for a typed object which is also reflectable
#define REFLECTABLE_OBJECT(TYPE) TYPED_OBJECT(TYPE); REFLECTABLE(TYPE);



#define MEMBERCLASSNAME(NAME) NAME##MemberClass
#define MEMBERCLASSINSTANCE(NAME) ((MEMBERCLASSNAME(NAME)*) MEMBERCLASSNAME(NAME)::instance())

#define PROPERTYCLASS(NAME) MEMBERCLASSNAME(NAME)//NAME##PropertyClass



#define PROPERTYCLASSINSTANCE(NAME) MEMBERCLASSINSTANCE(NAME) //( (PROPERTYCLASS(NAME) * ) PROPERTYCLASS(NAME)::instance())



// enables property reflection for the property <NAME> of type <TYPE> 
// this may only be used in a class which has been declared as REFLECTABLE and has both the set<NAME>(<TYPE>) and <TYPE> get<NAME>()const methods
//
#define ENABLE_PROPERTY_REFLECTION(TYPE,NAME)\
private:\
  typedef CurrentClassType NAME##OwningClassType;\
  class PROPERTYCLASS(NAME) : public virtual nspace::TypedProperty<NAME##OwningClassType,TYPE>{\
    TYPED_OBJECT( PROPERTYCLASS(NAME) );\
  public:\
    SINGLETON( PROPERTYCLASS(NAME) ){\
      setPropertyType(typeof(TYPE));\
      setName(#NAME);\
      setHasGetter(true);\
      setHasSetter(true);\
    }\
    void setTypedValue(NAME##OwningClassType *  object , TYPE value)const{\
      object->SETMETHOD(NAME)(value);\
    }\
    TYPE getTypedValue(const NAME##OwningClassType *  object)const{\
      return object->GETMETHOD(NAME)();\
    }\
  };\
private:\
  STATIC_INITIALIZER( NAME##Property , { \
    auto type = typeof(NAME##OwningClassType);\
    auto unconst = const_cast<nspace::Type*>(dynamic_cast<const nspace::Type*>(type));\
    unconst->Members()|=PROPERTYCLASSINSTANCE(NAME);\
  })


#define REFLECTABLE_CUSTOM_PROPERTY(TYPE,NAME,PROPERTYDECLARATION)\
  ENABLE_PROPERTY_REFLECTION(TYPE,NAME)\
  PROPERTYDECLARATION(TYPE,NAME)

// sets the propertydisplayname property of the property object created for the property specified by NAME (.... property)
#define DISPLAYNAME(NAME, DNAME)\
  STATIC_INITIALIZER(NAME##DisplayName, {MEMBERCLASSINSTANCE(NAME)->setDisplayName(DNAME);})

// sets the description of property specified by name
#define DESCRIPTION(NAME, DDESCRIPTION)\
  STATIC_INITIALIZER(NAME##Description, {MEMBERCLASSINSTANCE(NAME)->setDescription(DDESCRIPTION);})

// sets the default value for the property specified by NAME  (make sure the type is correct) also add the set to default method
#define DEFAULTVALUE(NAME,DEFAULTVALUE)\
  public:\
  void set##NAME##ToDefault(){PROPERTYCLASSINSTANCE(NAME)->setToDefaultValue(this);}\
private:\
  STATIC_INITIALIZER(NAME##DefaultValue, {static auto defaultvalue = DEFAULTVALUE; PROPERTYCLASSINSTANCE(NAME)->setDefaultValue(&defaultvalue);})

// sets the groupname of the property specified by NAME
#define GROUPNAME(NAME,GROUP)\
  STATIC_INITIALIZER(NAME##GroupName,MEMBERCLASSINSTANCE(NAME)->setGroupName(GROUP))

#define HIDDEN(NAME)\
  STATIC_INITIALIZER(NAME##Hidden,PROPERTYCLASSINSTANCE(NAME)->setIsVisible(false))

// sets the property or propertyset to navigatable (indicating that the property is a subclass of object)
#define NAVIGATABLE(CLASS, NAME) \
  STATIC_INITIALIZER(NAME##Navigatable,PROPERTYCLASSINSTANCE(NAME)->setIsNavigatable(true);PROPERTYCLASSINSTANCE(NAME)->setPropertyClass(typeof(CurrenClassType));)

#define ISPOINTER(NAME)\
  STATIC_INITIALIZER(NAME##Pointer,PROPERTYCLASSINSTANCE(NAME)->setIsPointer(true);)

#define OBJECTPOINTER(TYPE,NAME)\
  STATIC_INITIALIZER(NAME##ObjectPointer,\
  PROPERTYCLASSINSTANCE(NAME)->setIsPointer(true);\
  PROPERTYCLASSINSTANCE(NAME)->setObjectConverter([](void * ptr){ return dynamic_cast<Object*>(reinterpret_cast<TYPE*>(ptr));});\
  );

#define OBJECTPOINTERPROPERTY(TYPE,NAME)\
  OBJECTPOINTER(TYPE,NAME)\
  PROPERTY(TYPE*,NAME)


#define SERIALIZERARGUMENTS(TYPE) std::ostream & stream, const TYPE * value
#define DESERIALIZERARGUMENTS(TYPE) TYPE * value, std::istream & stream

#define SERIALIZEMETHODNAME(NAME) serialize##NAME
#define DESERIALIZEMETHODNAME(NAME) deserialize##NAME
#define SERIALIZESIGNATURE(TYPE,NAME) SERIALIZEMETHODNAME(NAME)(SERIALIZERARGUMENTS(TYPE))
#define DESERIALIZESIGNATURE(TYPE,NAME) DESERIALIZEMETHODNAME(NAME)(DESERIALIZERARGUMENTS(TYPE))
// macro for implementing serializing property <NAME> of type <TYPE>.  be sure to define the returntype as bool (See CUSTOMSERIALIZER macro)
#define serializeProperty(TYPE,NAME) SERIALIZESIGNATURE(TYPE,NAME)
// macro for implementing deserializing property <NAME> of type <TYPE>.  be sure to define the returntype as bool(See CUSTOMSERIALIZER macro)
#define deserializeProperty(TYPE,NAME) DESERIALIZESIGNATURE(TYPE,NAME)

// make sure to return if the deserialization was successful or not
#define CUSTOMDESERIALIZER(TYPE,NAME,CODE)\
  public:\
  static bool DESERIALIZESIGNATURE(TYPE,NAME) CODE;\
  private:\
class NAME##CustomDeserializer : public virtual TypedCustomDeserializer<TYPE>{\
public:\
  bool deserializeType(DESERIALIZERARGUMENTS(TYPE)){return DESERIALIZEMETHODNAME(NAME)(value,stream);};\
};\
  STATIC_INITIALIZER(NAME##CustomDeserializer,{PROPERTYCLASSINSTANCE(NAME)->setCustomDeserializer(new NAME##CustomDeserializer());})

// make sure to return if the serialization was successful or not
#define CUSTOMSERIALIZER(TYPE,NAME,CODE)\
  public:\
  static bool SERIALIZESIGNATURE(TYPE,NAME) CODE;\
  private:\
class NAME##CustomSerializer : public virtual TypedCustomSerializer<TYPE>{\
public:\
  bool serializeType(SERIALIZERARGUMENTS(TYPE)){return SERIALIZEMETHODNAME(NAME)(stream,value);};\
};\
  STATIC_INITIALIZER(NAME##CustomSerializer,{PROPERTYCLASSINSTANCE(NAME)->setCustomSerializer(new NAME##CustomSerializer());})

// defines a custom serializer for property <NAME>  
#define CUSTOMSERIALIZERS(TYPE,NAME,SERIALIZECODE,DESERIALIZECODE)\
  CUSTOMSERIALIZER(TYPE,NAME,SERIALIZECODE);\
  CUSTOMDESERIALIZER(TYPE,NAME,DESERIALIZECODE);


#define REFLECTABLE_PROPERTY(TYPE,NAME) REFLECTABLE_CUSTOM_PROPERTY(TYPE,NAME,SIMPLE_PROPERTY)
#define REFLECTABLE_NOTIFYING_PROPERTY(TYPE,NAME) REFLECTABLE_CUSTOM_PROPERTY(TYPE,NAME,NOTIFYING_PROPERTY)

// default property macro 
#define PROPERTY(TYPE,NAME) REFLECTABLE_NOTIFYING_PROPERTY(TYPE,NAME)

// creates a property for any nonpointer / nonreference field and addutionally allows access by reference
#define REF_PROP(TYPE,NAME) REFERENCE_PROPERTY(TYPE,NAME); PROPERTY(TYPE,NAME)



// Defines a reflectable property collection
#define PROPERTYCOLLECTION(TYPE,NAME,ONADD,ONREMOVE)\
private:\
  typedef CurrentClassType NAME##OwningClassType;\
class PROPERTYCLASS(NAME) : public virtual TypedPropertySetInfo<NAME##OwningClassType,TYPE>{\
public:\
  SINGLETON( PROPERTYCLASS(NAME) ){\
    setName(#NAME);\
  }\
  Set<TYPE> & getMutableSetReference( NAME##OwningClassType * object )const{\
  return object->NAME();\
}\
  const Set<TYPE> & getConstSetReference(const NAME##OwningClassType * object )const{\
  return object->NAME();\
}\
};\
  STATIC_INITIALIZER(NAME##PropertyClass, {  auto constType =  typeof(NAME##OwningClassType);\
  auto type = const_cast<nspace::Type*>(dynamic_cast<const nspace::Type*>(typeof(NAME##OwningClassType)));\
  type->Members()|= PROPERTYCLASSINSTANCE(NAME);});\
  PROPERTYSET(TYPE,NAME,ONADD,ONREMOVE);


// creates a collection of TYPE* objects which can be navigated
#define OBJECTPOINTERCOLLECTION(TYPE,NAME,ONADD,ONREMOVE)\
  PROPERTYCOLLECTION(TYPE*,NAME,ONADD,ONREMOVE);\
  STATIC_INITIALIZER( NAME##ObjectPointer ,\
  PROPERTYCLASSINSTANCE(NAME)->setIsPointerCollection(true);\
  PROPERTYCLASSINSTANCE(NAME)->setElementToObjectConverter([](void * ptr){ return dynamic_cast<Object*>(reinterpret_cast<TYPE*>(ptr));});\
  );




// creates a public method with the signature void <NAME>() and registers it at its typeinfo class
// only TYPED_OBJECT(<ClassName>) needs to be declared in the class were action is declared because ACTION needs
// access to Local ClassType function
#define ACTION(NAME) \
private:\
  typedef CurrentClassType NAME##ParentClassType;\
  class MEMBERCLASSNAME(NAME) : public virtual nspace::MethodInfo{\
    SINGLETON(MEMBERCLASSNAME(NAME)){\
      setName(#NAME);\
    }\
  public:\
    bool call(nspace::Object * object, void * arguments=0, void ** returnvalue=0)const{\
      auto typedObject = dynamic_cast<NAME##ParentClassType*>(object);\
      if(!typedObject)return false;\
      typedObject->NAME();\
      return true;\
    }\
  };\
  STATIC_INITIALIZER(NAME,{\
    auto typeInfo =  const_cast<nspace::Type*>(dynamic_cast<const nspace::Type * >(typeof(NAME##ParentClassType)));\
    typeInfo->Members().add(MEMBERCLASSINSTANCE(NAME));\
  });\
public:\
  void NAME()
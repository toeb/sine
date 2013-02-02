/**
 * Copyright (C) 2013 Tobias P. Becker
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the  rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * More information at: https://dslib.assembla.com/
 *
 */
#pragma once

#include <core/reflection/PropertyInfo.h>
#include <core/reflection/MethodInfo.h>
#include <core/reflection/TypedProperty.h>
#include <core/reflection/TypedPropertySetInfo.h>
#include <core/reflection/PropertyAdapter.h>
#include <core/reflection/MethodAdapter.h>
#include <core/PropertyChangingObject.h>
#include <core/patterns/Singleton.h>

/**
 * \brief to use reflection REFLECTABLE(<CLASSNAME>) needs to be stated once in the class. it
 *        creates multiple things:
 *        - properties() : a static set of const Propert * which contains all reflectable
 *        properties of a class
 *        - getProperty(string) : a static method for accessing a property
 *        - T getPropertyValue(string name) : a class member which returns the value of the
 *        specified property
 *        - setPropertyValue(string name) : a class member for setting the value of a specific
 *        property
 *        - (a private set of const properties called propertiesSet())
 *        WARNING:  Since Class Hierarchy is not yet supported it is not possible to reflect upon
 *        properties of supertypes
 *
 *        after REFLECTABLE(<CLASSNAME>) was called you may add reflectable properties by adding :
 *        - REFLECTABLE_CUSTOM_PROPERTY
 *        - REFLECTABLE_PROPERTY
 *        - REFLECTABLE_NOTIFYING_PROPERTY.
 *
 * \param TYPENAME  The typename.
 */
#define REFLECTABLE(TYPENAME) \
public: \
  template<typename T> \
  T getPropertyValue(const std::string & propertyname) const { \
    T val; \
    getPropertyValue(propertyname,val); \
    return val; \
  } \
  template<typename T> \
  void getPropertyValue(const std::string & propertyname,T & value) const { \
    auto prop = getProperty(propertyname); \
    if(!prop) return; \
    prop->get(value,*this); \
  } \
  template<typename T> \
  void setPropertyValue(const std::string & propertyname,const T &value){ \
    auto prop = getProperty(propertyname); \
    if(!prop) return; \
    prop->set(value,*this); \
  } \
  static const nspace::Set<const nspace::PropertyInfo*> & properties(){ \
    static nspace::Set<const nspace::PropertyInfo*> _properties = typeof(TYPENAME)->Properties(); \
    return _properties; \
  } \
  static const nspace::PropertyInfo * getProperty(const std::string & propertyname){ \
    auto p = typeof(TYPENAME)->getProperty(propertyname); \
    return p; \
  } \
  nspace::PropertyAdapter getPropertyAdapter(const std::string & name){ \
    return nspace::PropertyAdapter(dynamic_cast<nspace::Object*>(this),name); \
  } \
  nspace::MethodAdapter getMethodAdapter(const std::string & name){ \
    return nspace::MethodAdapter(dynamic_cast<nspace::Object*>(this),name); \
  } \
  static const nspace::MethodInfo * getMethodInfo(const std::string & methodName){ \
    return typeof(TYPENAME)->getMethodInfo(methodName); \
  } \
private:

/**
 * \brief shorthand for a typed object which is also reflectable TYPED_OBJECT enables that metadata
 *        about the class can be generated (getType method for instances of TYPE)
 *        Reflectable creates access methods to the objects members.
 *
 * \param TYPE  The type.
 */
#define REFLECTABLE_OBJECT(TYPE) TYPED_OBJECT(TYPE); REFLECTABLE(TYPE);

/**
 * \brief A macro that defines memberclassname.
 *
 * \param NAME  The name.
 */
#define MEMBERCLASSNAME(NAME) NAME ## MemberClass

/**
 * \brief A macro that defines memberclassinstance.
 *
 * \param NAME  The name.
 */
#define MEMBERCLASSINSTANCE(NAME) ((MEMBERCLASSNAME(NAME)*)MEMBERCLASSNAME(NAME) ::instance())

/**
 * \brief A macro that defines propertyclass.
 *
 * \param NAME  The name.
 */
#define PROPERTYCLASS(NAME) MEMBERCLASSNAME(NAME) //NAME##PropertyClass

/**
 * \brief A macro that defines propertyclassinstance.
 *
 * \param NAME  The name.
 */
#define PROPERTYCLASSINSTANCE(NAME) MEMBERCLASSINSTANCE(NAME) //( (PROPERTYCLASS(NAME) * ) PROPERTYCLASS(NAME)::instance())

/**
 * \brief enables property reflection for the property <NAME> of type <TYPE>
 *        this may only be used in a class which has been declared as REFLECTABLE and has both the
 *        set<NAME>(<TYPE>) and <TYPE> get<NAME>()const methods.
 *
 * \param TYPE  The type.
 * \param NAME  The name.
 */
#define ENABLE_PROPERTY_REFLECTION(TYPE,NAME) \
private: \
  typedef CurrentClassType NAME ## OwningClassType; \
  class PROPERTYCLASS(NAME) : public virtual nspace::TypedProperty<NAME ## OwningClassType,TYPE>{ \
    TYPED_OBJECT( PROPERTYCLASS(NAME) ); \
public: \
    SINGLETON( PROPERTYCLASS(NAME) ){ \
      setPropertyType(typeof(TYPE)); \
      setName(# NAME); \
      setHasGetter(true); \
      setHasSetter(true); \
    } \
    void setTypedValue(NAME ## OwningClassType *  object, TYPE value) const { \
      object->SETMETHOD(NAME) (value); \
    } \
    TYPE getTypedValue(const NAME ## OwningClassType *  object) const { \
      return object->GETMETHOD(NAME) (); \
    } \
  }; \
private: \
  STATIC_INITIALIZER( NAME ## Property, { \
                        auto type = typeof(NAME ## OwningClassType); \
                        auto unconst = const_cast<nspace::Type*>(dynamic_cast<const nspace::Type*>(type)); \
                        unconst->Members()|=PROPERTYCLASSINSTANCE(NAME); \
                      })

/**
 * \brief A macro that defines reflectable custom property.
 *
 * \param TYPE                The type.
 * \param NAME                The name.
 * \param PROPERTYDECLARATION The propertydeclaration.
 */
#define REFLECTABLE_CUSTOM_PROPERTY(TYPE,NAME,PROPERTYDECLARATION) \
  ENABLE_PROPERTY_REFLECTION(TYPE,NAME) \
  PROPERTYDECLARATION(TYPE,NAME)

/**
 * \brief sets the propertydisplayname property of the property object created for the property
 *        specified by NAME (.... property)
 *
 * \param NAME  The name.
 * \param DNAME The dname.
 */
#define DISPLAYNAME(NAME, DNAME) \
  STATIC_INITIALIZER(NAME ## DisplayName, {MEMBERCLASSINSTANCE(NAME)->setDisplayName(DNAME); })

/**
 * \brief sets the description of property specified by name.
 *
 * \param NAME          The name.
 * \param DDESCRIPTION  The ddescription.
 */
#define DESCRIPTION(NAME, DDESCRIPTION) \
  STATIC_INITIALIZER(NAME ## Description, {MEMBERCLASSINSTANCE(NAME)->setDescription(DDESCRIPTION); })

/**
 * \brief sets the default value for the property specified by NAME  (make sure the type is
 *        correct) also add the set to default method.
 *
 * \param NAME          The name.
 * \param DEFAULTVALUE  The defaultvalue.
 */
#define DEFAULTVALUE(NAME,DEFAULTVALUE) \
public: \
  void set ## NAME ## ToDefault(){PROPERTYCLASSINSTANCE(NAME)->setToDefaultValue(this); } \
private: \
  STATIC_INITIALIZER(NAME ## DefaultValue, {static auto defaultvalue = DEFAULTVALUE; PROPERTYCLASSINSTANCE(NAME)->setDefaultValue(&defaultvalue); })

/**
 * \brief sets the groupname of the property specified by NAME.
 *
 * \param NAME  The name.
 * \param GROUP The group.
 */
#define GROUPNAME(NAME,GROUP) \
  STATIC_INITIALIZER(NAME ## GroupName,MEMBERCLASSINSTANCE(NAME)->setGroupName(GROUP); )

/**
 * \brief A macro that defines hidden.
 *
 * \param NAME  The name.
 */
#define HIDDEN(NAME) \
  STATIC_INITIALIZER(NAME ## Hidden,PROPERTYCLASSINSTANCE(NAME)->setIsVisible(false); )

/**
 * \brief sets the property or propertyset to navigatable (indicating that the property is a
 *        subclass of object)
 *
 * \param CLASS The class.
 * \param NAME  The name.
 */
#define NAVIGATABLE(CLASS, NAME) \
  STATIC_INITIALIZER(NAME ## Navigatable,PROPERTYCLASSINSTANCE(NAME)->setIsNavigatable(true); PROPERTYCLASSINSTANCE(NAME)->setPropertyClass(typeof(CurrenClassType)); )

/**
 * \brief A macro that defines ispointer.
 *
 * \param NAME  The name.
 */
#define ISPOINTER(NAME) \
  STATIC_INITIALIZER(NAME ## Pointer,PROPERTYCLASSINSTANCE(NAME)->setIsPointer(true); )

/**
 * \brief A macro that defines objectpointer.
 *
 * \param TYPE  The type.
 * \param NAME  The name.
 */
#define OBJECTPOINTER(TYPE,NAME) \
  STATIC_INITIALIZER(NAME ## ObjectPointer, \
                     PROPERTYCLASSINSTANCE(NAME)->setIsPointer(true); \
                     PROPERTYCLASSINSTANCE(NAME)->setObjectConverter([] (void * ptr){ return dynamic_cast<Object*>(reinterpret_cast<TYPE*>(ptr)); }); \
                     );

/**
 * \brief A macro that defines objectpointerproperty.
 *
 * \param TYPE  The type.
 * \param NAME  The name.
 */
#define OBJECTPOINTERPROPERTY(TYPE,NAME) \
  OBJECTPOINTER(TYPE,NAME) \
  PROPERTY(TYPE*,NAME)

/**
 * \brief A macro that defines serializerarguments.
 *
 * \param TYPE  The type.
 */
#define SERIALIZERARGUMENTS(TYPE) std::ostream & stream, const TYPE * value

/**
 * \brief A macro that defines deserializerarguments.
 *
 * \param TYPE  The type.
 */
#define DESERIALIZERARGUMENTS(TYPE) TYPE * value, std::istream & stream

/**
 * \brief A macro that defines serializemethodname.
 *
 * \param NAME  The name.
 */
#define SERIALIZEMETHODNAME(NAME) serialize ## NAME

/**
 * \brief A macro that defines deserializemethodname.
 *
 * \param NAME  The name.
 */
#define DESERIALIZEMETHODNAME(NAME) deserialize ## NAME

/**
 * \brief A macro that defines serializesignature.
 *
 * \param TYPE  The type.
 * \param NAME  The name.
 */
#define SERIALIZESIGNATURE(TYPE,NAME) SERIALIZEMETHODNAME(NAME) (SERIALIZERARGUMENTS(TYPE))

/**
 * \brief A macro that defines deserializesignature.
 *
 * \param TYPE  The type.
 * \param NAME  The name.
 */
#define DESERIALIZESIGNATURE(TYPE,NAME) DESERIALIZEMETHODNAME(NAME) (DESERIALIZERARGUMENTS(TYPE))

/**
 * \brief macro for implementing serializing property <NAME> of type <TYPE>.  be sure to define the
 *        returntype as bool (See CUSTOMSERIALIZER macro)
 *
 * \param TYPE  The type.
 * \param NAME  The name.
 */
#define serializeProperty(TYPE,NAME) SERIALIZESIGNATURE(TYPE,NAME)

/**
 * \brief macro for implementing deserializing property <NAME> of type <TYPE>.  be sure to define
 *        the returntype as bool(See CUSTOMSERIALIZER macro)
 *
 * \param TYPE  The type.
 * \param NAME  The name.
 */
#define deserializeProperty(TYPE,NAME) DESERIALIZESIGNATURE(TYPE,NAME)

/**
 * \brief make sure to return if the deserialization was successful or not.
 *
 * \param TYPE  The type.
 * \param NAME  The name.
 * \param CODE  The code.
 */
#define CUSTOMDESERIALIZER(TYPE,NAME,CODE) \
public: \
  static bool DESERIALIZESIGNATURE(TYPE,NAME) CODE; \
private: \
  class NAME ## CustomDeserializer : public virtual TypedCustomDeserializer<TYPE>{ \
public: \
    bool deserializeType(DESERIALIZERARGUMENTS(TYPE)){return DESERIALIZEMETHODNAME(NAME) (value,stream); }; \
  }; \
  STATIC_INITIALIZER(NAME ## CustomDeserializer,{PROPERTYCLASSINSTANCE(NAME)->setCustomDeserializer(new NAME ## CustomDeserializer()); })

/**
 * \brief make sure to return if the serialization was successful or not.
 *
 * \param TYPE  The type.
 * \param NAME  The name.
 * \param CODE  The code.
 */
#define CUSTOMSERIALIZER(TYPE,NAME,CODE) \
public: \
  static bool SERIALIZESIGNATURE(TYPE,NAME) CODE; \
private: \
  class NAME ## CustomSerializer : public virtual TypedCustomSerializer<TYPE>{ \
public: \
    bool serializeType(SERIALIZERARGUMENTS(TYPE)){return SERIALIZEMETHODNAME(NAME) (stream,value); }; \
  }; \
  STATIC_INITIALIZER(NAME ## CustomSerializer,{PROPERTYCLASSINSTANCE(NAME)->setCustomSerializer(new NAME ## CustomSerializer()); })

/**
 * \brief defines a custom serializer for property <NAME>
 *
 * \param TYPE            The type.
 * \param NAME            The name.
 * \param SERIALIZECODE   The serializecode.
 * \param DESERIALIZECODE The deserializecode.
 */
#define CUSTOMSERIALIZERS(TYPE,NAME,SERIALIZECODE,DESERIALIZECODE) \
  CUSTOMSERIALIZER(TYPE,NAME,SERIALIZECODE); \
  CUSTOMDESERIALIZER(TYPE,NAME,DESERIALIZECODE);

/**
 * \brief A macro that defines reflectable property.
 *
 * \param TYPE  The type.
 * \param NAME  The name.
 */
#define REFLECTABLE_PROPERTY(TYPE,NAME) REFLECTABLE_CUSTOM_PROPERTY(TYPE,NAME,SIMPLE_PROPERTY)

/**
 * \brief A macro that defines reflectable notifying property.
 *
 * \param TYPE  The type.
 * \param NAME  The name.
 */
#define REFLECTABLE_NOTIFYING_PROPERTY(TYPE,NAME) REFLECTABLE_CUSTOM_PROPERTY(TYPE,NAME,NOTIFYING_PROPERTY)

/**
 * \brief default property macro.
 *
 * \param TYPE  The type.
 * \param NAME  The name.
 */
#define PROPERTY(TYPE,NAME) REFLECTABLE_NOTIFYING_PROPERTY(TYPE,NAME)

/**
 * \brief creates a property for any nonpointer / nonreference field and addutionally allows access
 *        by reference.
 *
 * \param TYPE  The type.
 * \param NAME  The name.
 */
#define REF_PROP(TYPE,NAME) REFERENCE_PROPERTY(TYPE,NAME); PROPERTY(TYPE,NAME)

/**
 * \brief Defines a reflectable property collection.
 *
 * \param TYPE      The type.
 * \param NAME      The name.
 * \param ONADD     The onadd.
 * \param ONREMOVE  The onremove.
 */
#define PROPERTYCOLLECTION(TYPE,NAME,ONADD,ONREMOVE) \
private: \
  typedef CurrentClassType NAME ## OwningClassType; \
  class PROPERTYCLASS(NAME) : public virtual TypedPropertySetInfo<NAME ## OwningClassType,TYPE>{ \
public: \
    SINGLETON( PROPERTYCLASS(NAME) ){ \
      setName(# NAME); \
    } \
    Set<TYPE> & getMutableSetReference( NAME ## OwningClassType * object ) const { \
      return object->NAME(); \
    } \
    const Set<TYPE> & getConstSetReference(const NAME ## OwningClassType * object ) const { \
      return object->NAME(); \
    } \
  }; \
  STATIC_INITIALIZER(NAME ## PropertyClass, {  auto type = const_cast<nspace::Type*>(dynamic_cast<const nspace::Type*>(typeof(NAME ## OwningClassType))); \
                                               type->Members()|= PROPERTYCLASSINSTANCE(NAME); }); \
  PROPERTYSET(TYPE,NAME,ONADD,ONREMOVE);

// creates a collection of TYPE* objects which can be navigated
#define OBJECTPOINTERCOLLECTION(TYPE,NAME,ONADD,ONREMOVE) \
  PROPERTYCOLLECTION(TYPE*,NAME,ONADD,ONREMOVE); \
  STATIC_INITIALIZER( NAME ## ObjectPointer, \
                      PROPERTYCLASSINSTANCE(NAME)->setIsPointerCollection(true); \
                      PROPERTYCLASSINSTANCE(NAME)->setElementToObjectConverter([] (void * ptr){ return dynamic_cast<Object*>(reinterpret_cast<TYPE*>(ptr)); }); \
                      );

/**
 * \brief creates a public method with the signature void <NAME>() and registers it at its typeinfo
 *        class only TYPED_OBJECT(<ClassName>) needs to be declared in the class were action is
 *        declared because ACTION needs access to Local ClassType function.
 *
 * \param NAME  The name.
 */
#define ACTION(NAME) \
private: \
  typedef CurrentClassType NAME ## ParentClassType; \
  class MEMBERCLASSNAME(NAME) : public virtual nspace::MethodInfo { \
    SINGLETON(MEMBERCLASSNAME(NAME)){ \
      setName(# NAME); \
      setOwningType(typeof(NAME ## ParentClassType));\
    } \
public: \
    bool call(nspace::Object * object, void * arguments=0, void ** returnvalue=0) const { \
      auto typedObject = dynamic_cast<NAME ## ParentClassType*>(object); \
      if(!typedObject) return false; \
      typedObject->NAME(); \
      return true; \
    } \
  }; \
  STATIC_INITIALIZER(NAME,{ \
                       auto typeInfo =  const_cast<nspace::Type*>(dynamic_cast<const nspace::Type * >(typeof(NAME ## ParentClassType))); \
                       typeInfo->Members().add(MEMBERCLASSINSTANCE(NAME)); \
                     }); \
public: \
  void NAME()

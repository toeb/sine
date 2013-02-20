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
/**
 * \file  core\properties\Properties.h
 *
 * \brief Declares Macros for uniform property definition.
 */
#pragma once
#include <core.preprocessor.h>
// for type helper function
#include <core/template/result_of_static_function.h>
#include <core/template/function_traits.h>

#define DS_CURRENT_TYPE_NAME CurrentType
#define DS_CURRENT_TYPE(CLASSNAME) typedef CLASSNAME DS_CURRENT_TYPE_NAME;

/**
 * \brief macro is replaced by the name for the property specified by NAME.   
 *        (NAME may be adorned with a extension etc NAME##Property)
 *        currenlty the name is just returned
 *
 * \param NAME  The name.
 */
#define DS_PROPERTY_NAME(NAME) NAME

/**
 * \brief A macro which is replaced by the Propertietype's name.
 *        Currently it is the concatenation of Propertyname and "PropertyType
 *        \example DS_PROPERTY_TYPE_NAME(Value) -> ValuePropertyType
 *
 * \param NAME  The name.
 */
#define DS_PROPERTY_TYPE_NAME(NAME) DS_CONCAT(DS_PROPERTY_NAME(NAME),PropertyType)

/**
 * \brief This macro is replaced the name of the helper function
 *
 * \param NAME  The name.
 */
#define DS_STATIC_TYPE_DEFINITION_HELPER_NAME(NAME) DS_CONCAT(___,DS_PROPERTY_NAME(NAME))
#define DS_PROPERTY_DEFINITION_HELPER_NAME(NAME)  DS_CONCAT(___,DS_PROPERTY_NAME(NAME))
#define DS_PROPERTY_DEFINITION_HELPER(NAME)  DS_PROPERTY_DEFINITION_HELPER_NAME(NAME)()const
/**
 * \brief defines the type of the property (using the Definition helper method to allow prepending the actual type only once)
 *  current usage: typedef <typename> DS_PROPERTY_TYPE_DEFINITION * this will change in future versions when microsoft fixes their compiler       
 * 
 * \param NAME  The name.
 */
//#define DS_PROPERTY_TYPE_DEFINITION(NAME) protected: typedef nspace::result_of_static_function< decltype( &DS_STATIC_TYPE_DEFINITION_HELPER_NAME(NAME) ) >::type DS_PROPERTY_TYPE_NAME (NAME); //this is the definition of the property type
//this would work if visual studio fixed the c1001 bug //#define DS_PROPERTY_TYPE_DEFINITION(NAME) protected: typedef nspace::function_traits< decltype(  &DS_PROPERTY_DEFINITION_HELPER_NAME(NAME) ) >::result_type DS_PROPERTY_TYPE_NAME (NAME); //this is the definition of the property type
// 
#define DS_PROPERTY_TYPE_DEFINITION(NAME) DS_CONCAT(_,DS_PROPERTY_TYPE_NAME(NAME)); protected: typedef DS_CONCAT(_,DS_PROPERTY_TYPE_NAME(NAME)) DS_PROPERTY_TYPE_NAME(NAME);
/**
 * \brief same as DS_PROPERTY_TYPE_DEFINITION(NAME) but works in template classes (added typename specifier)
 *
 * \param NAME  The name.
 */
#define DS_PROPERTY_TYPE_DEFINITION_TEMPLATED(NAME) /*private:  typedef typename nspace::result_of_static_function< decltype( &DS_STATIC_TYPE_DEFINITION_HELPER_NAME(NAME) ) >::type*/ DS_PROPERTY_TYPE_NAME (NAME);

//#define DS_PROPERTY_DEFINITION(NAME) /* Begginning of Property */ \
 // static DS_STATIC_TYPE_DEFINITION_HELPER_NAME(NAME) (); /*this should not create any overhead and is possible for any type*/ \
 // DS_PROPERTY_TYPE_DEFINITION(NAME) /* Define Property type */

#define DS_PROPERTY_DEFINITION(NAME) DS_PROPERTY_TYPE_DEFINITION(NAME)
  /* Begginning of Property */ 
  /*DS_PROPERTY_DEFINITION_HELPER(NAME); *//*this should not create any overhead and is possible for any type*/ 
  /*DS_PROPERTY_TYPE_DEFINITION(NAME)*/ /* Define Property type */


#define DS_PROPERTY_DEFINITION_TEMPLATED(NAME) \
  DS_PROPERTY_DEFINITION(NAME)\
  /*static DS_STATIC_TYPE_DEFINITION_HELPER_NAME(NAME) (); *//*this should not create any overhead and is possible for any type*/ \
  /*DS_PROPERTY_TYPE_DEFINITION_TEMPLATED(NAME) *//* Define Property type */

// there can be field storage pointer storage, refence storage and callback storage
//

#define DS_PROPERTY_STORAGE_NAME(NAME) DS_CONCAT(_, DS_PROPERTY_NAME(NAME))

#define DS_PROPERTY_STORAGE_TYPE_NAME(NAME) DS_CONCAT(DS_PROPERTY_NAME(NAME),StorageType)

#define DS_PROPERTY_STORAGE_TYPE_FIELD(NAME) typedef DS_PROPERTY_TYPE_NAME (NAME) DS_PROPERTY_STORAGE_TYPE_NAME (NAME);
#define DS_PROPERTY_STORAGE_TYPE_POINTER(NAME) typedef DS_PROPERTY_TYPE_NAME (NAME) * DS_PROPERTY_STORAGE_TYPE_NAME (NAME);
#define DS_PROPERTY_STORAGE_TYPE_REFERENCE(NAME) typedef DS_PROPERTY_TYPE_NAME (NAME) & DS_PROPERTY_STORAGE_TYPE_NAME (NAME);

#define DS_PROPERTY_STORAGE_FIELD(NAME) DS_PROPERTY_STORAGE_TYPE_FIELD(NAME) DS_PROPERTY_STORAGE_TYPE_NAME(NAME) DS_PROPERTY_STORAGE_NAME(NAME);
#define DS_PROPERTY_STORAGE_POINTER(NAME)  DS_PROPERTY_STORAGE_TYPE_POINTER(NAME) DS_PROPERTY_STORAGE_TYPE_NAME(NAME) DS_PROPERTY_STORAGE_NAME(NAME);
#define DS_PROPERTY_STORAGE_REFERENCE(NAME) DS_PROPERTY_STORAGE_TYPE_REFERENCE(NAME) DS_PROPERTY_STORAGE_TYPE_NAME(NAME) DS_PROPERTY_STORAGE_NAME(NAME);
#define DS_PROPERTY_STORAGE_CALLBACK(NAME)

#define DS_PROPERTY_STORAGE(NAME) DS_PROPERTY_STORAGE_NAME(NAME)

#define DS_PROPERTY_GETTER_NAME(NAME) get ## NAME
#define DS_PROPERTY_SETTER_NAME(NAME) set ## NAME


#define DS_PROPERTY_GETTER_SIGNATURE(NAME) DS_INLINE const DS_PROPERTY_TYPE_NAME(NAME) & DS_PROPERTY_GETTER_NAME(NAME) () const
#define DS_PROPERTY_SETTER_SIGNATURE(NAME) DS_INLINE void DS_PROPERTY_SETTER_NAME(NAME) (const DS_PROPERTY_TYPE_NAME(NAME) & value)
#define DS_PROPERTY_SETTER_SIGNATURE_RVALUE(NAME) DS_INLINE void DS_PROPERTY_SETTER_NAME(NAME) (DS_PROPERTY_TYPE_NAME(NAME) && value)

#define DS_PROPERTY_GETTER(NAME) DS_PROPERTY_GETTER_SIGNATURE(NAME)

#define DS_PROPERTY_SETTER(NAME) DS_PROPERTY_SETTER_SIGNATURE(NAME)

#define DS_PROPERTY_SETTER_RVALUE(NAME) DS_PROPERTY_SETTER_SIGNATURE_RVALUE(NAME)


#define DS_PROPERTY_AUTO_SETTER(NAME) DS_PROPERTY_SETTER(NAME){ DS_PROPERTY_STORAGE(NAME) = value; } //DS_PROPERTY_SETTER_RVALUE(NAME){ DS_PROPERTY_STORAGE(NAME) = value; }
#define DS_PROPERTY_AUTO_GETTER(NAME) DS_PROPERTY_GETTER(NAME){ return DS_PROPERTY_STORAGE(NAME); }


/*  It is relatively ugly but one could use define to set the propertyname
   #define DS_PROPERTY_NAME Value
   DEFINITION;
   private: FIELD_STORAGE;
   protected: virtual SETTER;
   public: GETTER;


   #undef DS_PROPERTY_NAME


 */


#define basic_property(NAME)      \
  DS_PROPERTY_DEFINITION(NAME)    \
private:                          \
 DS_PROPERTY_STORAGE_FIELD(NAME); \
public:                           \
  DS_PROPERTY_AUTO_GETTER(NAME);  \
  DS_PROPERTY_AUTO_SETTER(NAME)




#define DS_PROPERTY_SETTER_BEFORE_NAME(NAME) DS_CONCAT(DS_CONCAT(onBefore,NAME),Set)
#define DS_PROPERTY_SETTER_AFTER_NAME(NAME) DS_CONCAT(DS_CONCAT(onAfter,NAME),Set)
#define DS_PROPERTY_SETTER_BEFORE_SIGNATURE(NAME) void DS_INLINE DS_PROPERTY_SETTER_BEFORE_NAME(NAME) (const DS_PROPERTY_TYPE_NAME(NAME) & newvalue, bool & cancel)
#define DS_PROPERTY_SETTER_AFTER_SIGNATURE(NAME) void DS_INLINE DS_PROPERTY_SETTER_AFTER_NAME(NAME) ()


#define validating_property(NAME)                                 \
  DS_PROPERTY_DEFINITION(NAME)                                    \
private:                                                          \
  DS_PROPERTY_STORAGE_FIELD(NAME);                                \
public:                                                           \
  DS_PROPERTY_AUTO_GETTER(NAME);                                  \
public:                                                           \
  DS_PROPERTY_SETTER(NAME){                                       \
    bool cancel=false;                                            \
    DS_PROPERTY_SETTER_BEFORE_NAME(NAME) (value,cancel);          \
    if(cancel) return;                                            \
    DS_PROPERTY_STORAGE(NAME)=value;                              \
  }                                                               \
private:                                                          \
  DS_PROPERTY_SETTER_BEFORE_SIGNATURE(NAME)


#define DS_MINIMAL_GET(NAME) DS_PROPERTY_GETTER(NAME){ return DS_PROPERTY_STORAGE(NAME);  }
#define DS_MINIMAL_SET(NAME) DS_PROPERTY_SETTER(NAME){ DS_PROPERTY_STORAGE(NAME) = value; }

#define DS_CURRENT_CLASS(CLASSNAME) typedef CLASSNAME CurrentClassType;


#define DS_PROPERTY_MARKER(NAME) DS_CONCAT(NAME,PropertyMarker)
#define DS_PROPERTY_MARKER_DEFINITION(NAME) struct DS_PROPERTY_MARKER (NAME){ };

/*  This works with MSVC however specialization of template methods inside of a class is not part of the C++ standard --> GCC fails
    Also a limitation (albeit a negligable one) is that you may not use this as a  local struct because of templating
   #define DS_PROPERTY_EXTENSION_BEFORE_SET_NAME onBeforePropertySet
   #define DS_PROPERTY_EXTENSION_AFTER_SET_NAME onAfterPropertySet
   #define DS_PROPERTY_EXTENSION_BEFORE_GET_NAME onBeforePropertyGet

   #define DS_PROPERTY_EXTENSION_BEFORE_SET  template<typename MarkerType,typename ValueType> DS_INLINE bool DS_PROPERTY_EXTENSION_BEFORE_SET_NAME(const ValueType & value){return false;}
   #define DS_PROPERTY_EXTENSION_AFTER_SET   template<typename MarkerType> DS_INLINE void DS_PROPERTY_EXTENSION_AFTER_SET_NAME(){}
   #define DS_PROPERTY_EXTENSION_BEFORE_GET  template<typename MarkerType> DS_INLINE void DS_PROPERTY_EXTENSION_BEFORE_GET_NAME()const{}

   #define DS_PROPERTY_EXTENSION_BEFORE_SET_IMPLEMENTATION(NAME) template<> DS_INLINE bool DS_PROPERTY_EXTENSION_BEFORE_SET_NAME<DS_PROPERTY_MARKER(NAME),  DS_PROPERTY_TYPE_NAME(NAME)>(const DS_PROPERTY_TYPE_NAME(NAME) & newvalue)
   #define DS_PROPERTY_EXTENSION_AFTER_SET_IMPLEMENTATION(NAME)  template<> DS_INLINE void DS_PROPERTY_EXTENSION_AFTER_SET_NAME< DS_PROPERTY_MARKER(NAME)>()
   #define DS_PROPERTY_EXTENSION_BEFORE_GET_IMPLEMENTATION(NAME) template<> DS_INLINE void DS_PROPERTY_EXTENSION_BEFORE_GET_NAME< DS_PROPERTY_MARKER(NAME)>()const


   #define DS_PROPERTY_EXTENSION_METHODS\
   DS_PROPERTY_EXTENSION_BEFORE_SET\
   DS_PROPERTY_EXTENSION_AFTER_SET\
   DS_PROPERTY_EXTENSION_BEFORE_GET\

   #define DS_PROPERTY_BEFORE_SET(NAME) DS_PROPERTY_EXTENSION_BEFORE_SET_IMPLEMENTATION(NAME) //DS_INLINE bool before##NAME##Set(const DS_PROPERTY_TYPE_NAME(NAME) & value)
   #define DS_PROPERTY_AFTER_SET(NAME) DS_PROPERTY_EXTENSION_AFTER_SET_IMPLEMENTATION(NAME)//DS_INLINE void after##NAME##Set()
   #define DS_PROPERTY_BEFORE_GET(NAME) DS_PROPERTY_EXTENSION_BEFORE_GET_IMPLEMENTATION(NAME)//DS_INLINE void before##NAME##Get()const

   #define beforeSet(NAME) DS_PROPERTY_BEFORE_SET(NAME)
   #define afterSet(NAME) DS_PROPERTY_AFTER_SET(NAME)
   #define beforeGet(NAME) DS_PROPERTY_BEFORE_GET(NAME)

   #define DS_PROPERTY_SETTER_EXTENDED(NAME) DS_PROPERTY_SETTER(NAME){ if( DS_PROPERTY_EXTENSION_BEFORE_SET_NAME<DS_PROPERTY_MARKER(NAME),DS_PROPERTY_TYPE_NAME(NAME)>(value))return; DS_PROPERTY_STORAGE(NAME) = value; DS_PROPERTY_EXTENSION_AFTER_SET_NAME<DS_PROPERTY_MARKER(NAME)>();}
   #define DS_PROPERTY_GETTER_EXTENDED(NAME) DS_PROPERTY_GETTER(NAME){ DS_PROPERTY_EXTENSION_BEFORE_GET_NAME<DS_PROPERTY_MARKER(NAME)>(); return DS_PROPERTY_STORAGE(NAME); }


   #define DS_PROPERTY_EXTENDED(NAME)\
   DS_PROPERTY_DEFINITION(NAME)\
   DS_PROPERTY_MARKER_DEFINITION(NAME)\
   DS_PROPERTY_STORAGE_FIELD(NAME)\
   public: DS_PROPERTY_GETTER_EXTENDED(NAME)\
   public: DS_PROPERTY_SETTER_EXTENDED(NAME)
 */
// This is plattform indepenedent.  it uses overloading and a markertypes to call default/custom extension methods
// it works for classes and structs in namespaces, classes as well as methods
// furthermore you must not define the general (empty implementations) of the extension methods in the class if every property defines all extensions
// I strongly believe( have not checked) that there is no overhead when the compiler is done optimizing code.  I may be mistaken
// these do not work with templated arguments you must use the correct
#define DS_PROPERTY_EXTENSION_BEFORE_SET_NAME onBeforePropertySet
#define DS_PROPERTY_EXTENSION_AFTER_SET_NAME onAfterPropertySet
#define DS_PROPERTY_EXTENSION_BEFORE_GET_NAME onBeforePropertyGet

#define DS_PROPERTY_EXTENSION_BEFORE_SET  DS_INLINE bool DS_PROPERTY_EXTENSION_BEFORE_SET_NAME(const void * marker, const void * value){return false; }
#define DS_PROPERTY_EXTENSION_AFTER_SET   DS_INLINE void DS_PROPERTY_EXTENSION_AFTER_SET_NAME(const void * marker){}
#define DS_PROPERTY_EXTENSION_BEFORE_GET  DS_INLINE void DS_PROPERTY_EXTENSION_BEFORE_GET_NAME(const void * marker) const {}

#define DS_PROPERTY_EXTENSION_BEFORE_SET_IMPLEMENTATION(NAME) DS_INLINE bool DS_PROPERTY_EXTENSION_BEFORE_SET_NAME(const DS_PROPERTY_MARKER(NAME)*,  const DS_PROPERTY_TYPE_NAME(NAME) * newvalue)
#define DS_PROPERTY_EXTENSION_AFTER_SET_IMPLEMENTATION(NAME)  DS_INLINE void DS_PROPERTY_EXTENSION_AFTER_SET_NAME(const DS_PROPERTY_MARKER(NAME)*)
#define DS_PROPERTY_EXTENSION_BEFORE_GET_IMPLEMENTATION(NAME) DS_INLINE void DS_PROPERTY_EXTENSION_BEFORE_GET_NAME(const DS_PROPERTY_MARKER(NAME)*) const


#define DS_PROPERTY_EXTENSION_METHODS \
  DS_PROPERTY_EXTENSION_BEFORE_SET   \
  DS_PROPERTY_EXTENSION_AFTER_SET    \
  DS_PROPERTY_EXTENSION_BEFORE_GET   \

#define DS_PROPERTY_BEFORE_SET(NAME) DS_PROPERTY_EXTENSION_BEFORE_SET_IMPLEMENTATION(NAME) //DS_INLINE bool before##NAME##Set(const DS_PROPERTY_TYPE_NAME(NAME) & value)
#define DS_PROPERTY_AFTER_SET(NAME) DS_PROPERTY_EXTENSION_AFTER_SET_IMPLEMENTATION(NAME) //DS_INLINE void after##NAME##Set()
#define DS_PROPERTY_BEFORE_GET(NAME) DS_PROPERTY_EXTENSION_BEFORE_GET_IMPLEMENTATION(NAME) //DS_INLINE void before##NAME##Get()const

#define DS_PROPERTY_MARKER_INSTANCE(NAME) static_cast<const DS_PROPERTY_MARKER(NAME)*>(0)
#define DS_PROPERTY_SETTER_EXTENDED(NAME) DS_PROPERTY_SETTER(NAME){ if(DS_PROPERTY_EXTENSION_BEFORE_SET_NAME(DS_PROPERTY_MARKER_INSTANCE(NAME), &value)) return; DS_PROPERTY_STORAGE(NAME) = value; DS_PROPERTY_EXTENSION_AFTER_SET_NAME(DS_PROPERTY_MARKER_INSTANCE(NAME)); }
#define DS_PROPERTY_GETTER_EXTENDED(NAME) DS_PROPERTY_GETTER(NAME){ DS_PROPERTY_EXTENSION_BEFORE_GET_NAME(DS_PROPERTY_MARKER_INSTANCE(NAME)); return DS_PROPERTY_STORAGE(NAME); }


#define DS_PROPERTY_EXTENDED(NAME)            \
  DS_PROPERTY_DEFINITION(NAME)                \
  DS_PROPERTY_MARKER_DEFINITION(NAME)         \
  DS_PROPERTY_STORAGE_FIELD(NAME)             \
public: DS_PROPERTY_GETTER_EXTENDED(NAME)     \
public: DS_PROPERTY_SETTER_EXTENDED(NAME)

#define extensible_property_class DS_PROPERTY_EXTENSION_METHODS
#define extensible_property(NAME) DS_PROPERTY_EXTENDED(NAME)
#define before_set(NAME) DS_PROPERTY_BEFORE_SET(NAME)
#define after_set(NAME) DS_PROPERTY_AFTER_SET(NAME)
#define before_get(NAME) DS_PROPERTY_BEFORE_GET(NAME)

// todo:
/*
   #define DS_PROPERTY_EXTENDED_TEMPLATED(NAME)\
   DS_PROPERTY_DEFINITION_TEMPLATED(NAME)    \
   DS_PROPERTY_MARKER_DEFINITION(NAME)       \
 */
 namespace nspace{
   
 void ping();
 }
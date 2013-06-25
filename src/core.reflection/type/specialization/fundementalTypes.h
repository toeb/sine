#pragma once

#include <core.reflection/type/TypeInfo.h>



namespace nspace{

#define DS_ADD_GLOBAL_QUALIFIER(X) ::X
  // std::is_integral -> true (signed char==char==char_16, wcahr_t = char32_t 
#define DS_INTEGRAL_TYPES bool,char,/*char16_t,char32_t,*/wchar_t,/*signed char,*/ short int, int , long int , long long int, unsigned char, unsigned short int,unsigned int, unsigned long int, unsigned long long int
#define DS_INTEGRAL_TYPES_QUALIFIED DS_REDUCE_COMMA(DS_ADD_GLOBAL_QUALIFIER,DS_INTEGRAL_TYPES)
  
  // std::is_floating_point -> true
#define DS_FLOATING_POINT_TYPES float, double, long double
#define DS_FLOATING_POINT_TYPES_QUALIFIED DS_REDUCE_COMMA(DS_ADD_GLOBAL_QUALIFIER,DS_INTEGRAL_TYPES)
  // std::is_void ->true
#define DS_VOID_TYPE void
#define DS_NULL_POINTER_TYPE std::nullptr_t
  // std::is_fundemental-> true
#define DS_FUNDEMENTAL_TYPES DS_INTEGRAL_TYPES,DS_FLOATING_POINT_TYPES,DS_VOID_TYPE,DS_NULL_POINTER_TYPE

#define META(X)
#define META_DEFAULTCONSTRUCTOR(X)
#define DS_DEFAULT_CONSTRUCTOR_DISABLE(X)

  // meta information for fundemental types
  DS_FOREACH(META_DEFAULTCONSTRUCTOR,DS_INTEGRAL_TYPES);
  DS_FOREACH(META_DEFAULTCONSTRUCTOR,DS_FLOATING_POINT_TYPES);
  META(void);
  DS_DEFAULT_CONSTRUCTOR_DISABLE(void);

  META(::std::nullptr_t)


  // argument can now be meta'd  
  META(Argument);

}
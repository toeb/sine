#pragma once

#ifndef nspace
#define nspace ds
#endif

#include <float.h>//for DBL_MAX
#include <iostream>

typedef unsigned int uint;
typedef unsigned char byte;

#define EPSILON 1.0E-9
#define PI 3.14159

// define the floating point type Real
#ifdef USE_DOUBLES
typedef double Real;
#define REAL_MAX DBL_MAX
#define REAL_MIN DBL_MIN
#else
typedef float Real;

#define REAL_MAX FLT_MAX
#define REAL_MIN FLT_MIN
#endif

#ifndef __FUNCSIG__
#define __FUNCSIG__ __PRETTY_FUNCTION__
#endif
#ifndef WIN32
#define __FUNCSIG__ __PRETTY_FUNCTION__
#endif

// macro for dynamic linking
#ifdef DLL
#ifdef DLL_EXPORT
#define DS_API __declspec(dllexport)
#else
#define DS_API __declspec(dllimport)
#endif
#else 
#define DS_API
#endif






// for visual studio i'll disalbe warning about inheritance via dominance  4250 is inheritance via dominance warning, 4822 is for locally declared methods without body
#pragma warning( disable : 4250 4822 )
// considered adding 4018 for signed unsigned comparison


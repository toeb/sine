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

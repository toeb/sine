#pragma once

#ifndef nspace
#define nspace ds
#endif

#include <float.h>//for DBL_MAX

typedef unsigned int uint;
typedef unsigned char byte;

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
  

#define ERRORSTREAM std::cerr
#ifndef WIN32 
#define __FUNCSIG__ __PRETTY_FUNCTION__
#endif
#define ERROR(x) ERRORSTREAM << "Error '"<<x<<"' in " << __FUNCSIG__ << " at line "<<__LINE__<<std::endl;

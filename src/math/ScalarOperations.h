#pragma once

#include <config.h>


#include <math/ScalarConstants.h>
#include <math/operations/NullaryOperation.h>
#include <math/operations/UnaryOperation.h>
#include <math/operations/BinaryOperation.h>

// include all scalar operations
#include <math/operations/Absolute.h>
//#include <math/operations/Addition.h>
//#include <math/operations/ArcusCosinus.h>
#include <math/operations/ArcusSinus.h>
//#include <math/operations/ArcusTangens.h>
//#include <math/operations/ArcusTangens2.h>
#include <math/operations/Cosinus.h>
//#include <math/operations/Division.h>
//#include <math/operations/Identity.h>
//#include <math/operations/Maximum.h>
//#include <math/operations/Minimum.h>
//#include <math/operations/Multiplication.h>
//#include <math/operations/Reciprocal.h>
#include <math/operations/Signum.h>
//#include <math/operations/Sinus.h>
//#include <math/operations/SquareRoot.h>
//#include <math/operations/Subtraction.h>
//#include <math/operations/Tangens.h>
//#include <math/operations/Zero.h>

#define NULLARY_SHORTHAND(NAME , OP)  template<typename T> T NAME(){ T result; scalar::Operation<T,operation::Nullary,operation::OP>::operation(result); return result; }
#define UNARY_SHORTHAND(NAME , OP)  template<typename T> T NAME(const T a){T result; scalar::Operation<T,operation::Unary,operation::OP>::operation(result, a); return result;}
#define BINARY_SHORTHAND(NAME , OP)  template<typename T> T NAME(const T a,const T b){T result; scalar::Operation<T,operation::Binary,operation::OP>::operation(result, a,b); return result;}

namespace nspace{
  namespace math{
  namespace scalar{
    // define shorthand functions for all operations
    UNARY_SHORTHAND(signum,Signum);
    UNARY_SHORTHAND(cosine,Cosinus);
    UNARY_SHORTHAND(absolute,Absolute);
    UNARY_SHORTHAND(arcusSinus,ArcusSinus);



  }
  }
}
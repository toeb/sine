#pragma once
#include <config.h>
#include <math.operation/NullaryOperation.h>
#include <math.scalar/operationcodes.h>
#include <math.scalar/constants.h>
namespace nspace{
namespace math{
  namespace operation{
namespace scalar{
template<typename T>
class Operation<T,math::operation::Nullary,opcodes::SquareRootOfTwo >{
public:
  static inline void operation(T & a){
    a = M_SQRT2;
  }        
};
}
}
}
}

#pragma once
#include <config.h>
#include <math/operations/NullaryOperation.h>
#include <math/operations/OperationCodes.h>
#include <math/ScalarConstants.h>
namespace nspace{
namespace math{
namespace scalar{
template<typename T>
class Operation<T, operation::Nullary,operation::Pi >{
public:
  static inline void operation(T & a){
    a = M_PI;
  }        
};
}
}
}

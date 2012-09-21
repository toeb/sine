#pragma once
#include <config.h>
#include <math/operations/NullaryOperation.h>
#include <math/operations/OperationCodes.h>
namespace nspace{
namespace math{
namespace scalar{
template<typename T>
class Operation<T, operation::Nullary,operation::Zero >{
public:
  static inline void operation(T & a){
    a = 0.0;
  }        
};
}
}
}

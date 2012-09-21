#pragma once
#include <config.h>
#include <math/operations/UnaryOperation.h>
#include <math/operations/OperationCodes.h>
#include <cmath>
namespace nspace{
namespace math{
namespace scalar{

  template<typename T>
  class Operation<T,operation::Unary, operation::Absolute>{
  public:
    static inline void  operation(T & b, const T &  a){
      b = std::abs(a);
    }
  };

}
}
}


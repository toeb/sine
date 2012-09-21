#pragma once
#include <config.h>
#include <math/operations/UnaryOperation.h>
#include <math/operations/OperationCodes.h>
#include <cmath>
namespace nspace{
namespace math{
namespace scalar{

  template<T>
  class UnaryOperation<T, operation::SquareRoot>{
  public:
    static inline T operation(const T a){
      return std::sqrt(a);
    }
  };

  template<typename T>
  typedef UnaryOperation<T,operation::SquareRoot> SquareRoot;
  
}
}
}


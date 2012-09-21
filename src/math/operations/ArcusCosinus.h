#pragma once
#include <config.h>
#include <math/operations/UnaryOperation.h>
#include <math/operations/OperationCodes.h>
#include <cmath>
namespace nspace{
namespace math{
namespace scalar{

  template<T>
  class UnaryOperation<T, operation::ArcusCosinus>{
  public:
    static inline T operation(const T a){
      return std::acos(a);
    }
  };

  template<typename T>
  typedef UnaryOperation<T,operation::ArcusCosinus> ArcusCosinus;
  
}
}
}

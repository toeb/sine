#pragma once
#include <config.h>
#include <math/operations/UnaryOperation.h>
#include <math/operations/OperationCodes.h>
#include <cmath>
namespace nspace{
namespace math{
namespace scalar{

  template<typename T>
  class Operation<T,operation::Unary, operation::Signum>{
  public:
    static inline void operation(T & b ,const T & a){
      if(a >=0.0){ b = 1.0 ; return;}
      if(a < 0.0){ b = -1.0 ;return;}
    }
  };

}
}
}


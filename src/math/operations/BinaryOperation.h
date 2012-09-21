#pragma once
#include <math/operations/Operation.h>

namespace nspace{
namespace math{
namespace scalar{

  typedef OperationCode BinaryOperationCode;

  template<typename T, BinaryOperationCode code>
  class Operation<T, operation::Binary, code>{
  public:
    static inline void operation(T & c, const T & a, const T & b){
      ERROR("UNIMPLEMENTED BINARY OPERATION");

    }        
  };


      

}
}
}

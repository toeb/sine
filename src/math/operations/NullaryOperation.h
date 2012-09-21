#pragma once
#include <config.h>

#include <math/operations/Operation.h>

namespace nspace{
namespace math{
namespace scalar{

  typedef OperationCode NullaryOperationCode;
  template<typename T, NullaryOperationCode code>
  class Operation<T, operation::Nullary, code>{
  public:
    static inline void operation(T & a){
      
    }        
  };
      

}
}
}

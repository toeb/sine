#pragma once
#include <config.h>
#include <math/operations/Operation.h>

namespace nspace{
  namespace math{
    namespace scalar{      
      typedef OperationCode UnaryOperationCode;
      template<typename T, UnaryOperationCode code>
      class Operation<T, operation::Unary, code>{
      public:
        static inline void operation(T & b, const T & a){
          ERROR("USING UNIMPLEMENTED UNARY FUNCTION ");
        }        
      };


      
    }
  }
}
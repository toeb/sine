#pragma once
#include <config.h>


namespace nspace{
  namespace math{
    namespace scalar{      
      typedef uint OperationCode;
      namespace operation{
      enum OperationType{
        Nullary,
        Unary,
        Binary
      };

      }
      template<typename T, operation::OperationType type, OperationCode code>
      class Operation{
      public:
        
      };
    }
  }
}
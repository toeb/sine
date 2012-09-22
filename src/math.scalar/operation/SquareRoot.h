#pragma once
#include <config.h>
#include <math.operation/UnaryOperation.h>
#include <math.scalar/OperationCodes.h>
#include <cmath>
namespace nspace{
namespace math{
  namespace operation{
namespace scalar{

template<typename T>
class Operation<T,operation::Unary, opcodes::SquareRoot>{
public:
  static inline void operation(T & b ,const T & a){
    b = std::sqrt(a);
  }
};

}
}
}
}


#pragma once
#include <common/Config.h>
#include <math/operations/MatrixScalarMultiplication.h>
namespace nspace{
  template<typename MatrixQuotient,typename MatrixDividend, typename ScalarDivisor>
  class MatrixScalarDivisionInPlace{
  public:
    static inline void operation(MatrixQuotient & quotient, const MatrixDividend & dividend, const ScalarDivisor & divisor){
      ScalarDivisor factor;
      ScalarOperations<ScalarDivisor>::reciprocal(factor,divisor);
      MatrixScalarMultiplication<MatrixQuotient,MatrixDividend,ScalarDivisor>::operation(quotient,dividend,factor);
    }
  };
}
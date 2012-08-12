#pragma once
#include <common/Config.h>

namespace nspace{
  template<typename Product, typename MatrixFactor, typename ScalarFactor>
  class MatrixScalarMultiplication{
  public:
    static inline void operation(Product & product, const MatrixFactor & a, const ScalarFactor & d){
      for(int i=0; i < a.rows(); i++){
        for(int j=0; j < a.cols(); j++){
          product(i,j)=a(i,j)*d;
        }
      }
    }
  };
}
#pragma once
#include <config.h>

namespace nspace{
  template<typename Product, typename MatrixFactor, typename ScalarFactor>
  class MatrixScalarMultiplication{
  public:
    static inline void operation(Product & product, const MatrixFactor & a, const ScalarFactor & d){
      product.resize(a.rows(),a.cols(),false);
      for(int i=0; i < a.rows(); i++){
        for(int j=0; j < a.cols(); j++){
          product(i,j)=a(i,j)*d;
        }
      }
    }
  };
}
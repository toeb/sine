#pragma once
#include <config.h>

namespace nspace{
  template<typename C, typename A, typename B>
  class MatrixSubtraction{
  public:
    static inline void operation(C & c, const A & a, const B & b){
      c.resize(a.rows(),a.cols(),false);
      for(int i=0; i < a.rows(); i++){
        for(int j=0; j < a.cols(); j++){
          c(i,j)=a(i,j)-b(i,j);
        }
      }
    }
  };
}
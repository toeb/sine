#pragma once
#include <config.h>

namespace nspace{
  template<typename MatTransposed, typename Mat>
  class MatrixTranspose{
  public:
    static inline void operation(MatTransposed & AT, const Mat & A){
      AT.resize(A.cols(),A.rows());
      for(int i=0; i < A.rows(); i++){
        for(int j=0; j < A.cols(); j++){            
          AT(j,i)=A(i,j);         
        }
      }
    }
  };

}

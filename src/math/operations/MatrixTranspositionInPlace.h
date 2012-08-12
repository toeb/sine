#pragma once
#include <common/Config.h>

namespace nspace{
 
  template<typename Mat>
  class MatrixTransposeInPlace{
  public:
    static inline void operation(Mat & AT){
      Mat A = AT;
      AT.resize(A.cols(),A.rows(),false);
      for(int i=0; i < A.rows(); i++){
        for(int j=0; j < A.cols(); j++){            
          AT(j,i)=A(i,j);         
        }
      }
    }
  };
}
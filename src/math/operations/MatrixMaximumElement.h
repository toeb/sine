#pragma once
#include <config.h>

namespace nspace{
  template<typename ScalarResult, typename MatrixInput>
  class MatrixMaximumElement{
  public:
    static inline void operation(ScalarResult & maximum, const MatrixInput & mat){
      maximum = mat(0,0);
      for(int i=0; i < mat.rows();i++){
        for(int j=0; j < mat.cols();j++){
          if(maximum < mat(i,j))maximum=mat(i,j);
        }
      }
    }
  };
}
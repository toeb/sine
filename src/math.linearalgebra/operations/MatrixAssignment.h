#pragma once
#include <config.h>

namespace nspace{
  template<typename MatA, typename MatB>
  class MatrixAssign{
  public:
    static inline void operation(MatA &  result, const MatB & val){
      if(!result.resize(val.rows(), val.cols(),false)){
        std::cout << "MatrixAssign: could not resize result matrix "<<std::endl;
        return;
      }
      for(int i=0; i < result.rows(); i++){
        for(int j=0; j < result.cols(); j++){
          result(i,j)=val(i,j);
        }
      }
    }
  };
}
#pragma once
#include <config.h>

namespace nspace{
  template<typename T, typename Mat>
  class MatrixSetConstant{
  public:
    static inline void operation(Mat &  result, const T & val){
      for(int i=0; i < result.rows(); i++){
        for(int j=0; j < result.cols(); j++){
          result(i,j)=val;
        }
      }
    }
  };
}
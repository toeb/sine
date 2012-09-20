#pragma once
#include <common/Config.h>

namespace nspace{
  template<typename T, typename Mat>
  class MatrixAccessElement{
  public:
    inline static  T operation(const Mat mat,int i, int j){
      return mat.elementAt(i,j);
    }
    inline static  T operation(const Mat mat,int i){
      return mat.elementAt(i/mat.rows(), i % mat.cols());
    }
  };
}

#pragma once
#include <common/Config.h>

namespace nspace{
  template<typename T, typename Mat>
  class MatrixAccessElement{
  public:
    inline static  T operation(int i, int j){
      return Mat.elementAt(i,j);
    }
    inline static  T operation(int i){
      return Mat.elementAt(i/Mat.rows(), i % Mat.cols());
    }
  };
}
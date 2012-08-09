#pragma once
#include <common/Config.h>

namespace nspace{
  template<typename Sum, typename Summand1, typename Summand2>
  class MatrixAddition{
  public:
    static inline void operation(Sum & sum, const Summand1 & a, const Summand2 & b){
      for(int i=0; i < a.rows(); i++){
        for(int j=0; j < a.cols(); j++){
          sum(i,j)=a(i,j)+b(i,j);
        }
      }
    }
  };
}
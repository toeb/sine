#pragma once
#include <config.h>

namespace nspace{
  template<typename T, typename VecA, typename VecB>
 class VectorInnerProduct{
  public:
    static inline void operation(T &  result, const VecA & a, const VecB & b){
      if(a.size()!=b.size()){
   /*     ERROR("vector sizes donot match");*/
        return;
      }
      result = 0.0;
      for(int  i=0; i < a.size(); i++){
        result += a(i)*b(i);
      }
    }
  };
}


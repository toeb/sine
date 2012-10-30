#pragma once
#include <config.h>

namespace nspace{
 template<typename Result, typename VecA, typename VecB>
 class VectorOuterProduct{
  public:
    static inline void operation(Result &  result, const VecA & a, const VecB & b){
      if(result.rows()!=a.size()){
        //ERROR("incompatible sizes");
        return;
      }
      if(result.cols()!=b.size()){        
        //ERROR("incompatible sizes");
        return;
      }

      for(int  i=0; i < a.size(); i++){
        for(int j=0; j < b.size(); i++){
          result(i,j)=a(i)*b(j);
        }
      }
    }
  };
}


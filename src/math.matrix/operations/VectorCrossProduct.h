#pragma once
#include <config.h>

namespace nspace{
  
template<typename VecC, typename VecA, typename VecB>
 class VectorCrossProduct{
  public:
    static inline void operation(VecC &  c, const VecA & a, const VecB & b){
    if(a.size()!=3||b.size()!=3||c.size()!=3){
      ERROR("onyl possible on vector of size 3");
      return;
    }
    c(0)=a(1)*b(2)-a(2)*b(1);
    c(1)=a(2)*b(0)-a(0)*b(2);
    c(2)=a(0)*b(1)-a(1)*b(0);
      
    }
  };
} 

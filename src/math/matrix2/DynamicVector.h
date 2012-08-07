#pragma once

#include <math/types/DynamicMatrix.h>


namespace nspace{
  namespace matrix2{
  template<typename T>
class DynamicVector : public DynamicMatrix<T>{
public:
  inline T & operator()(int i){
    return _data[i];
  }
  inline const T & operator()(int i)const{
    return _data[i];
  }
};
  }
}

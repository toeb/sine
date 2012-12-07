#pragma once
#include <config.h>
namespace nspace{
  template<typename TypeA, typename TypeB>
  class MatrixTypeSelector{
  public: 
    typedef TypeA Type;
  };

  template<typename MatrixType>
  class MatrixTypeSelector<MatrixType,double>{
  public: 
    typedef MatrixType Type;
  };


}
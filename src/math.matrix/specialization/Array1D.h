#pragma once

#include <math.matrix/operations/MatrixTypeSelector.h>
namespace nspace{

  template<typename T, size_t n,typename MatrixType> SpecializeTypeSelectorPartially(T[n],MatrixType,MatrixType);
  template<typename T, size_t n,size_t m,typename MatrixType> SpecializeTypeSelectorPartially(T[n][m],MatrixType,MatrixType);
  template<typename T, typename MatrixType> SpecializeTypeSelectorPartially(T*,MatrixType,MatrixType);
  template<typename T, typename MatrixType> SpecializeTypeSelectorPartially(T**,MatrixType,MatrixType);
  

}

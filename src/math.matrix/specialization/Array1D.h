#pragma once
#include <math.matrix/operations/MatrixIndexType.h>
#include <math.matrix/operations/MatrixTypeSelector.h>
#include <math.matrix/operations/MatrixColumnTraits.h>
#include <math.matrix/operations/MatrixRowTraits.h>
#include <math.matrix/operations/MatrixTraits.h>
namespace nspace{
  
  template<typename T, size_t n> SpecializeMatrixIndexType(T[n],size_t);
  template<typename T, size_t n> SpecializeMatrixFixedSizeRows(T[n]);
  template<typename T, size_t n> SpecializeMatrixFixedSizeColumns(T[n]);
  template<typename T, size_t n> SpecializeMatrixCoefficientType(T[n],T);
  
  template<typename T, size_t n,typename MatrixType> SpecializeTypeSelectorPartially(T[n],MatrixType,MatrixType);
  
  
  template<typename T, size_t n,size_t m> SpecializeMatrixIndexType(T[n][m],size_t);
  template<typename T, size_t n,size_t m> SpecializeMatrixFixedSizeRows(T[n][m]);
  template<typename T, size_t n,size_t m> SpecializeMatrixFixedSizeColumns(T[n][m]);
  template<typename T, size_t n, size_t m> SpecializeMatrixCoefficientType(T[n][m],T);

  template<typename T, size_t n,size_t m,typename MatrixType> SpecializeTypeSelectorPartially(T[n][m],MatrixType,MatrixType);


  template<typename T> SpecializeMatrixIndexType(T*, size_t);
  template<typename T> SpecializeMatrixCoefficientType(T*, T);
  template<typename T, typename MatrixType> SpecializeTypeSelectorPartially(T*,MatrixType,MatrixType);

  
  template<typename T> SpecializeMatrixIndexType(T**, size_t);
  template<typename T> SpecializeMatrixCoefficientType(T**, T);
  template<typename T, typename MatrixType> SpecializeTypeSelectorPartially(T**,MatrixType,MatrixType);
  
  
  // specialization for 2d array
  // specializeation for 1d array


}

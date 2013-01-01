#pragma once
#include <config.h>
#include <math.matrix/operations/MatrixDimensionTraits.h>

namespace nspace{
  
  template<typename MatrixType>
  class MatrixRowTraits{
  public:
    static const DimensionTraits Traits = Dynamic;
  };
  #define RowTraits(TYPE) MatrixColumnTraits<TYPE>::Traits;

}
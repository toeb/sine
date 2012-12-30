#pragma once

#include <config.h>
#include <math.matrix/operations/MatrixDimensionTraits.h>
namespace nspace{
  template<typename MatrixType>
  class MatrixColumnTraits{
  public:
    DimensionTraits Traits = Unknown;
  };

}
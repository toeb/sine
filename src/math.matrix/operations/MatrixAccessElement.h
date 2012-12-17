#pragma once
#include <config.h>


namespace nspace{
  template<typename Matrix>
  class MatrixCoefficient{
  public:
    typedef Real Type;
  };
  
  template<typename Matrix>
  class MatrixIndex{
  public:
    typedef int Type;
  };
  template<typename Matrix>
  class MatrixSize{
  public:
    typedef int Type;
  };


  template<typename Coeff, typename Mat>
  class MatrixAccessElement{
  public:
    inline static const Coeff & operation(
      const Mat&  mat,
      const uint & i, 
      const uint & j){
      return mat(i,j);
    }
    inline static  Coeff & operation(
      Mat&  mat,
      const uint& i, 
      const uint & j){
      return mat(i,j);
    }
  };
}

#pragma once

#include <math.matrix/Matrix.h>
namespace nspace{
  
  template<typename MatrixType>
  class MatrixFacade : public Matrix<typename coefficientTypeOfType(MatrixType), typename indexTypeOfType(MatrixType), typename indexTypeOfType(MatrixType)>{
  private:
    MatrixType & matrix; 
  public:
    inline MatrixFacade(MatrixType & matrix):matrix(matrix){}
    typedef typename indexTypeOfType(MatrixType) Index;
    typedef typename coefficientTypeOfType(MatrixType) Coefficient;
    inline Coefficient & operator()(Index  i,  Index  j){
      return coefficient(matrix,i,j);
    }
    inline const Coefficient & operator()(Index  i,Index  j)const{
      // /todo cconst casts are bad.
      return coefficient(const_cast<MatrixType&>(matrix),i,j);
    }

    inline Index rows()const{return nspace::rows(matrix);}
    inline Index cols()const{return nspace::cols(matrix);}
  };

  class ObservableMatrix{

  };

  template<typename VectorType>
  class VectorFacade{
  private:
    VectorType & vector;
  public:
    inline  VectorFacade(VectorType & vector):vector(vector){}
    CoefficientAndIndexAliasForType(VectorType);
    inline  Coefficient & operator()(const Index & i){
      return coefficient(vector,i);
    }
    inline  Coefficient operator()(const Index & i)const{
      return coefficient(vector,i);
    }
    inline Coefficient & operator()(const Index & i, const Index & j){
      return coefficient(vector,i);
    }
    inline Coefficient operator()(const Index & i, const Index & j)const{
      return coefficient(vector,i);
    }
    inline Index size()const{return rows(vector);}
    inline Index rows()const{return nspace::rows(vector);}
    inline Index cols()const{return nspace::cols(vector);}
  };

  class ObservableVector{

  };



  template<typename MatrixType>
  auto wrapMatrix(MatrixType & mat)->MatrixFacade<MatrixType>{return MatrixFacade<MatrixType>(mat);}
  template<typename VectorType>
  auto wrapVector(VectorType & vector)->VectorFacade<VectorType>{return VectorFacade<VectorType>(vector);}
}
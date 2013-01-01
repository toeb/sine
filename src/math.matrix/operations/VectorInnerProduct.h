#pragma once
#include <config.h>
#include <math.matrix/operations/MatrixCoefficientType.h>
#include <math.matrix/operations/MatrixIndexType.h>
#include <math.matrix/operations/MatrixTypeSelector.h>
#include <math.matrix/operations/MatrixAddition.h>
#include <math.matrix/operations/MatrixMultiplication.h>
#include <math.matrix/operations/MatrixBinaryOperation.h>
namespace nspace{
  
  BinaryMatrixOperationOtherReturnType(dot,coefficientTypeOfType(typename returnType(A,B)));


  template<typename T, typename VecA, typename VecB>
  class VectorInnerProduct{
  public:
    static inline void operation(T & result, const VecA & a, const VecB & b){
      typedef typename coefficientTypeOfType(VecA) CoeffA;
      typedef typename coefficientTypeOfType(VecB) CoeffB;
      typedef typename indexTypeOfType(VecA) Index;      
      Index rowCount = rows(a);
      Index colCount = cols(a);
      result = 0;
      for(Index i=0; i < rowCount; i++){
        add(result,result, multiply<T,CoeffA,CoeffB>(coefficient(a,i,0), coefficient(b,i,0)));
      }
    }
  };

  BinaryOperationImplementation(dot){VectorInnerProduct<C,A,B>::operation(c,a,b);}

}

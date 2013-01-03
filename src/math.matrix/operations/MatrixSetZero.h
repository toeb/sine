#pragma once
#include <math.matrix/operations/MatrixCoefficientAccess.h>
#include <math.matrix/operations/MatrixRowCount.h>
#include <math.matrix/operations/MatrixColumnCount.h>
#include <math.matrix/operations/MatrixTraits.h>
#include <math.matrix/operations/MatrixBinaryOperation.h>
namespace nspace{



  NullaryMatrixOperation(zeros);


template<typename MatrixType>
class MatrixZero{
public:
  static inline void operation(MatrixType & matrix){
    CoefficientAndIndexAliasForType(MatrixType);
    if(isScalarMatrix<MatrixType>()){
      coefficient(matrix,0,0)=0;
      return;
    }
    
    Index rowCount = rows(matrix);
    Index colCount = cols(matrix);
    for(Index i = 0; i < rowCount; i++)
      for(Index j =0; j < colCount; j++)
        zeros(coefficient(matrix,i,j));
  }
};
NullaryOperationImplementation(zeros){
  MatrixZero<A>::operation(a);
}


}
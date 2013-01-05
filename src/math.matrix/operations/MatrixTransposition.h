#pragma once

#include<math.matrix/operations/MatrixOperations.h>
namespace nspace{

  template<typename AT, typename A> inline void tranpose(AT & at, const A & a);
  

  /**
   * \brief Transposes a matrix. The Matrix AT may not be the  same matrix as AT
   *        use MatrixTransposeInplace instead 
   *        \todo implement transpose inplace, transpose squared in place
   *
   * \tparam  typename MatrixTypeAT Type of the typename matrix type a t.
   * \tparam  typename MatrixTypeA  Type of the typename matrix type a.
   * \param parameter1  The first parameter.
   */
  template<typename MatrixTypeAT, typename MatrixTypeA>
  MatrixOperationClass(Transpose){
    MatrixOperationMethod(MatrixTypeAT & AT, const MatrixTypeA & A){
      
      if(isScalarMatrix<MatrixTypeAT>()){
        // scalars are already transposed
        assignMatrixBlindly(AT,A);
        return;
      }
      // if A is MxN then AT needs to be NxM
      if(!ensureMatrixDimension(AT,cols(A),rows(A))){
        throw "Transpose: cannot ensure needed matrix dimensions";
      }
      // actually transpose the matrix
      matrixForEach(A){
        transpose(coefficient(AT,j,i),coefficient(A,i,j));
      }
    }
  };
  UnaryOperationImplementation(transpose){
    OperationMatrixTranspose<B,A>::operation(b,a);
  }
}

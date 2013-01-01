#pragma once
#include <config.h>

#include <math.matrix/operations/MatrixCoefficientAccess.h>
#include <math.matrix/operations/MatrixRowCount.h>
#include <math.matrix/operations/MatrixColumnCount.h>
#include <math.matrix/operations/MatrixDimensionCheck.h>
#include <math.matrix/operations/MatrixMultiplication.h>
#include <math.matrix/operations/MatrixSubtraction.h>
#include <math.matrix/operations/MatrixTypeSelector.h>
#include <math.matrix/operations/MatrixBinaryOperation.h>

namespace nspace{

  /**
   * \brief  cross product operation for 3x1 vectors
   *
   */
  BinaryMatrixOperation(cross);

  /**
   * \brief performs the cross product .
   */
  template<typename VecC, typename VecA, typename VecB>
  class VectorCrossProduct{
  public:
    static inline void operation(VecC &  c, const VecA & a, const VecB & b){
      typedef typename coefficientTypeOfType(VecA) CoeffA;
      typedef typename coefficientTypeOfType(VecB) CoeffB;
      typedef typename coefficientTypeOfType(VecC) CoeffC;

      typedef typename indexTypeOfType(VecC) Index;
      Index rowCount = rows(c);
      //assert(rowCount==3) 
      Index i = 0;
      subtract(coefficient(c,0,i),multiply<CoeffC,CoeffA,CoeffB>(coefficient(a,1,i),coefficient(b,2,i)), multiply<CoeffC,CoeffA,CoeffB>(coefficient(a,2,i),coefficient(b,1,i)));
      subtract(coefficient(c,1,i),multiply<CoeffC,CoeffA,CoeffB>(coefficient(a,2,i),coefficient(b,0,i)), multiply<CoeffC,CoeffA,CoeffB>(coefficient(a,0,i),coefficient(b,2,i)));
      subtract(coefficient(c,2,i),multiply<CoeffC,CoeffA,CoeffB>(coefficient(a,0,i),coefficient(b,1,i)), multiply<CoeffC,CoeffA,CoeffB>(coefficient(a,1,i),coefficient(b,0,i)));
      
    }
  };

  //Implementation

  BinaryOperationImplementation(cross){VectorCrossProduct<C,A,B>::operation(c,a,b);}
  
}

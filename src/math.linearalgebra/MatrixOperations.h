#pragma once 
#include <stdio.h>
#include <iostream>
#include <functional>
#include <config.h>

#include <math.linearalgebra/ScalarOperations.h>
#include <math.linearalgebra/operations/MatrixAdditionInPlace.h>
#include <math.linearalgebra/operations/MatrixAddition.h>
#include <math.linearalgebra/operations/MatrixAssignment.h>
#include <math.linearalgebra/operations/MatrixConvolution.h>
#include <math.linearalgebra/operations/MatrixFilter.h>
#include <math.linearalgebra/operations/MatrixFrobeniusNorm.h>
#include <math.linearalgebra/operations/MatrixInversion.h>
#include <math.linearalgebra/operations/MatrixMinimumElement.h>
#include <math.linearalgebra/operations/MatrixMaximumElement.h>
#include <math.linearalgebra/operations/MatrixMultiplicationInPlace.h>
#include <math.linearalgebra/operations/MatrixMultiplication.h>
#include <math.linearalgebra/operations/MatrixNegationInPlace.h>
#include <math.linearalgebra/operations/MatrixNegation.h>
#include <math.linearalgebra/operations/MatrixNormalization.h>
#include <math.linearalgebra/operations/MatrixMultiplication.h>
#include <math.linearalgebra/operations/MatrixAllocate.h>
#include <math.linearalgebra/operations/MatrixDeallocate.h>
#include <math.linearalgebra/operations/MatrixAccessElement.h>
#include <math.linearalgebra/operations/MatrixScalarDivisionInPlace.h>
#include <math.linearalgebra/operations/MatrixScalarDivision.h>
#include <math.linearalgebra/operations/MatrixScalarMultiplicationInPlace.h>
#include <math.linearalgebra/operations/MatrixScalarMultiplication.h>
#include <math.linearalgebra/operations/MatrixSetConstant.h>
#include <math.linearalgebra/operations/MatrixSetFunction.h>
#include <math.linearalgebra/operations/MatrixSubtractionInPlace.h>
#include <math.linearalgebra/operations/MatrixSubtraction.h>
#include <math.linearalgebra/operations/MatrixInversionSymmetric.h>
#include <math.linearalgebra/operations/MatrixTranspositionInPlace.h>
#include <math.linearalgebra/operations/MatrixTransposition.h>
#include <math.linearalgebra/operations/VectorCrossProduct.h>
#include <math.linearalgebra/operations/VectorInnerProduct.h>
#include <math.linearalgebra/operations/VectorOuterProduct.h>
#include <math.linearalgebra/operations/VectorToCrossProductMatrix.h>
#include <math.linearalgebra/operations/QuaternionMultiplication.h>
#include <math.linearalgebra/operations/QuaternionConjugation.h>
#include <math.linearalgebra/operations/QuaternionToRotationMatrix.h>
#include <math.linearalgebra/operations/MatrixBlockAssign.h>
#include <math.linearalgebra/operations/MatrixBlockExtract.h>
#include <math.linearalgebra/operations/MatrixElementWiseMultiplication.h>
#include <math.linearalgebra/operations/MatrixElementWiseDivision.h>
#include <math.linearalgebra/operations/MatrixReduce.h>
#include <math.linearalgebra/operations/MatrixReduceSum.h>
#include <math.linearalgebra/operations/MatrixScalarAddition.h>
#include <math.linearalgebra/operations/MatrixScalarSubtraction.h>
#include <math.linearalgebra/operations/MatrixCompare.h>
#include <math.linearalgebra/operations/MatrixInversion.h>
#include <math.linearalgebra/operations/MatrixInversionSymmetric.h>
#include <math.linearalgebra/operations/MatrixCartesianToHomogenousCoordinates.h>
#include <math.linearalgebra/operations/MatrixExportData.h>
#include <math.linearalgebra/operations/MatrixImportData.h>
#include <math.linearalgebra/operations/MatrixResize.h>
#include <math.linearalgebra/operations/MatrixSubtractionConstant.h>
#include <math.linearalgebra/operations/MatrixElementWiseUnary.h>
#include <math.linearalgebra/operations/MatrixElementWiseBinary.h>
#include <math.linearalgebra/operations/MatrixPad.h>


namespace nspace{  
  namespace MatrixOps{

    template<typename MatA, typename Vec>
    inline void crossProductMatrix(MatA & a_star, const Vec& a){
      VectorToCrossProductMatrix<MatA,Vec>::operation(a_star,a);
    }

    template<typename MatA, typename MatB>
    inline void negate(MatA & result, const MatB & orig){
      MatrixNegation<MatA,MatB>::operation(result,orig);
    }

    template<typename Vec3A ,typename Vec3B, typename Vec3C>
    inline void crossProduct(Vec3C & c, const Vec3A & a, const Vec3B & b){
      VectorCrossProduct<Vec3C,Vec3A,Vec3B>::operation(c,a,b);
    }

    template<typename Mat>
    inline void resize(Mat & mat, uint rows, uint cols, bool setToZero){
      MatrixResize<Mat>::operation(mat,rows,cols,setToZero);   
    }
    

    template<typename MatType,typename BlockType>
    inline void setBlock(MatType & target, const BlockType & source, uint rowoffset, uint coloffset){
      MatrixBlockAssign<BlockType,MatType>::operation(target,source,rowoffset,coloffset);
    }

    template<typename BlockType, typename MatType>
    inline void getBlock(BlockType & block, const MatType & mat, uint rowoffset, uint coloffset){
      MatrixBlockExtract<BlockType,MatType>::operation(block,mat,rowoffset,coloffset);
    }

    template<typename T, typename TargetType>
    inline void assign(TargetType & target, const T* source){
      MatrixAssignData<T,TargetType>::operation(target,source);
    }

    template<typename T, typename SourceType>
    inline void copyTo(T * target, const SourceType & source){
      MatrixCopyToPointer<T,SourceType>::operation(target,source);
    }
    template<typename T, typename VectorTypeA, typename VectorTypeB>
    inline void innerProduct(T & result, const VectorTypeA & a, const VectorTypeB & b){
      VectorInnerProduct<T,VectorTypeA,VectorTypeB>::operation(result,a,b);
    }

    template<typename Result,typename Mat>
    inline void maximum(Result & result, const Mat & mat){
      MatrixMaximumElement<Result,Mat>::operation(result,mat);
    }
    template<typename Mat>
    inline Real maximum(const Mat & mat){
      Real result;
      maximum(result,mat);
      return result;
    }

    template<typename C, typename A, typename B>
    inline void elementWiseMultiply(C & result, const A & a, const B& b ){
      MatrixElementWiseMultiply<C,A,B>::operation(result,a,b);
    }
    template<typename C, typename A, typename B>
    inline void elementWiseDivide(C & result, const A & a, const B& b ){
      MatrixElementWiseDivide<C,A,B>::operation(result,a,b);
    }
    template<typename OutputMatrix, typename InputMatrix>
    void padMatrix(OutputMatrix & out, const InputMatrix & inputMatrix,uint rowsTop, uint rowsBottom, uint colsLeft, uint colsRight){
      MatrixPad<OutputMatrix,InputMatrix>::operation(out,inputMatrix, rowsTop,  rowsBottom,  colsLeft,  colsRight);
    }

  template<typename OutputMatrix, typename InputMatrix, typename KernelMatrix>
  void convolve(OutputMatrix & result, const InputMatrix & original, const KernelMatrix & kernel){
    MatrixConvolution<OutputMatrix,InputMatrix,KernelMatrix,Real>::operation(result,original,kernel);
  }

  template<typename MatA, typename MatB>
  void compareMatrix(bool & result, const MatA & a, const MatB & b, Real epsilon = EPSILON){
    MatrixCompare<MatA,MatB,Real>::operation(result,a,b,epsilon);
  }


  template<typename OutputMatrix, typename InputMatrix, typename KernelMatrix>
  void convolveSame(OutputMatrix & result, const InputMatrix & original, const KernelMatrix & kernel, int borderStrategy=0){
    uint rowsTop = kernel.rows()/2-1+kernel.rows()%2;
    uint rowsBottom = kernel.rows()/2;
    uint colsLeft = kernel.cols()/2-1+kernel.cols()%2;
    uint colsRight = kernel.cols()/2;
    InputMatrix padded;
    padMatrix(padded,original,rowsTop,rowsBottom,colsLeft,colsRight);
    MatrixConvolution<OutputMatrix,InputMatrix,KernelMatrix,Real>::operation(result,padded,kernel);
  }

  template<typename OutputMatrix, typename InputMatrix, typename FilterFunction, typename FilterArgument>
  void filter(OutputMatrix & result, const InputMatrix & original, FilterFunction filter,uint width, uint height){
    MatrixFilter<OutputMatrix,InputMatrix,FilterFunction,FilterArgument>::operation(result,original,filter,width,height);
  }

  template<typename C, typename A, typename B>
  void add(C & c, const A& a, const B & b){
    MatrixAddition<C,A,B>::operation(c,a,b);
  }
  template<typename C, typename A, typename B>
  void subtract(C & c, const A& a, const B & b){
    MatrixSubtraction<C,A,B>::operation(c,a,b);
  }
  template<typename C, typename A, typename B>
  void multiplyMatrix(C & c, const A& a, const B & b){
    MatrixMultiplication<Real,C,A,B>::operation(c,a,b);
  }
  template<typename C, typename A, typename B>
  void multiplyScalar(C & c, const A& a, const B & s){
    MatrixScalarMultiplication<C,A,B>::operation(c,a,s);
  }

  template<typename A, typename B>
  inline void cart2hom(A & hom, const B & car){
    MatrixCartesianToHomogenousCoordinates<A,B>::operation(hom,car);
  }

  template<typename A, typename B>
  inline void hom2car(A & cart, const B & hom){
    MatrixHomogenousToCartesianCoordinates<A,B>::operation(cart,hom);
  }
  
  template<typename InvertedMatrixType, typename InputMatrixType> 
  void invertSymmetricMatrix(InvertedMatrixType & inv, const InputMatrixType & symmetricMatrix){
    MatrixInversion<InvertedMatrixType,InputMatrixType,MatrixProperty::Symmetric>::operation(inv,symmetricMatrix);
  }
  template<typename InvertedMatrixType, typename InputMatrixType>
  void invertMatrix(InvertedMatrixType & inv, const InputMatrixType & matrix){
    MatrixInversion<InvertedMatrixType,InputMatrixType,MatrixProperty::Symmetric>::operation(inv,matrix);
  }
  
  };

  
}

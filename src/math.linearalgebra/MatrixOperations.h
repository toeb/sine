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
#include <math.linearalgebra/operations/MatrixElementWiseBinaryOperation.h>
#include <math.linearalgebra/operations/MatrixElementWiseUnaryOperation.h>
#include <math.linearalgebra/operations/MatrixElementWiseMultiplication.h>
#include <math.linearalgebra/operations/MatrixElementWiseDivision.h>
#include <math.linearalgebra/operations/MatrixReduce.h>
#include <math.linearalgebra/operations/MatrixReduceSum.h>
#include <math.linearalgebra/operations/MatrixScalarAddition.h>
#include <math.linearalgebra/operations/MatrixScalarSubtraction.h>
#include <math.linearalgebra/operations/MatrixCompare.h>
#include <math.linearalgebra/operations/MatrixInversion.h>
#include <math.linearalgebra/operations/MatrixInversionSymmetric.h>



namespace nspace{

  

  template<typename MatrixResult, typename MatrixSummandA, typename ScalarSummandB>
  class MatrixAdditionConstant{
  public:
    static inline void operation(MatrixResult & c, const MatrixSummandA & a, const ScalarSummandB & b){
      c.resize(a.rows(),a.cols(),false);
      for(int i=0; i < a.rows(); i++){
        for(int j=0; j < a.cols(); j++){
          c(i,j)=a(i,j)+b;
        }
      }
    }
  };
  template<typename MatrixResult, typename Matrix, typename Scalar>
  class MatrixSubtractionConstant{
  public:
    static inline void operation(MatrixResult & c, const Matrix & a, const Scalar & b){
      c.resize(a.rows(),a.cols(),false);
      for(int i=0; i < a.rows(); i++){
        for(int j=0; j < a.cols(); j++){
          c(i,j)=a(i,j)-b;
        }
      }
    }
  };
  

  template<typename MatHom,typename MatCart>
  class MatrixCartesianToHomogenousCoordinates{
  public:
    static inline void operation(MatHom & h, const MatCart & c){
      h.resize(c.rows()+1,c.cols(),false);
      for(int i=0; i < c.rows(); i++){
        for(int j=0; j <c.cols();j++){
          h(i,j)=c(i,j);
        }
      }
      for(int j=0;j <h.cols(); j++){
        h(c.rows(),j)=1;
      }
    }
  };
  
  template<typename MatCart,typename MatHom>
  class MatrixHomogenousToCartesianCoordinates{
  public:
    static inline void operation(MatCart & c, const MatHom & h){
      c.resize(h.rows()-1,h.cols,false);
      for(int i=0; i < c.rows(); i++){
        for(int j=0; j < c.cols(); j++){
          c(i,j) = h(i,j) / h(c.rows(),j);
        }
      }
    }
  };

  template<typename T>
  class MatrixOperations{
  public:
  
 


    template<typename MatrixType>
    static inline void negate(MatrixType & result,const MatrixType & m){
      for(int i=0; i < result.rows(); i++){
        for(int j=0; j < result.cols(); j++){
          result(i,j)=-m(i,j);
        }
      }
    }   
    
    
    
  };
  
  template<typename C,typename A, typename B>
  class MatrixElementWiseMultiply{
  public:
    static inline void operation(C & c, const A &  a, const B & b){
      if(a.rows() != b.rows() ||a.cols()!=b.cols()){
        std::cerr<< __FUNCSIG__ << ": Dimensions mismatch" <<std::endl;
        return;
      }
      c.resize(a.rows(),a.cols(),false);
      for(int i=0; i < a.rows(); i++){
        for(int j=0; j < a.cols(); j++){
          c(i,j)=a(i,j)*b(i,j);
        }
      }
    }
  };

  template<typename OutputMatrix, typename MatrixFactorA, typename MatrixFactorB>
  class MatrixMultiplyElementWise{
  public:
    static inline void operation(OutputMatrix & c, const MatrixFactorA & a, const MatrixFactorB &  b){
      if(a.rows()!=b.rows()||a.cols()!=b.cols())return;
      c.resize(a.rows(), a.cols(),false);
      for(int i=0; i < a.rows();i++){
        for(int j=0; j < a.cols();j++){
          c(i,j)=a(i,j)*b(i,j);
        }
      }
    }
  };

  template<typename C,typename A, typename B>
  class MatrixElementWiseDivide{
  public:
    static inline void operation(C & c, const A &  a, const B & b){
      if(a.rows() != b.rows() ||a.cols()!=b.cols()){
        std::cerr<< __FUNCSIG__ << ": Dimensions mismatch" <<std::endl;
        return;
      }
      c.resize(a.rows(),a.cols(),false);
      for(int i=0; i < a.rows(); i++){
        for(int j=0; j < a.cols(); j++){
          c(i,j)=a(i,j)/b(i,j);
        }
      }
    }
  };

  template<typename T>
  class ScalarArcusTangens{
  public:
    static inline void operation(T & c, const T & a){
      c = atan(a);
    }
  };

  template<typename C,typename A, typename B, typename OP>
  class MatrixElementWiseBinary{
  public:
    static inline void operation(C & c, const A &  a, const B & b){
      if(a.rows() != b.rows() ||a.cols()!=b.cols()){
        std::cerr<< __FUNCSIG__ << ": Dimensions mismatch" <<std::endl;
        return;
      }
      c.resize(a.rows(),a.cols(),false);
      for(int i=0; i < a.rows(); i++){
        for(int j=0; j < a.cols(); j++){
          OP::operation(c(i,j), a(i,j),b(i,j));
        }
      }
    }
  };
  template<typename C,typename A,typename OP>
  class MatrixElementWiseUnary{
  public:
    static inline void operation(C & c, const A &  a){      
      c.resize(a.rows(),a.cols(),false);
      for(int i=0; i < a.rows(); i++){
        for(int j=0; j < a.cols(); j++){
          OP::operation(c(i,j), a(i,j));
        }
      }
    }
  };
  template<typename T, typename SourceType>
  class MatrixCopyToPointer{
  public:
    static inline void operation(T * data, const SourceType & source){
      //slow implementation copies every element
      for(uint i=0; i < source.size(); i++){
        data[i] = source(i);
      }
    }
  };
  
  template<typename T, typename TargetType>
  class MatrixAssignData{
  public:
    static inline void operation(TargetType  & target, const T * source){
      for(uint i=0; i < target.size(); i++){
        target(i) = source[i];
      }
    }
  };
  
  template<typename TargetType>
  class MatrixResize{
  public:
    static inline void operation(TargetType  & target, uint rows, uint cols, bool setToZero){
     target.resize(rows,cols);      
     if(setToZero) MatrixSetConstant<Real,TargetType>::operation(target,val);
    }
  };
  
  namespace MatrixOps{
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


  /*
  template<typename T>
  inline void symmInverse(const StaticMatrix<T,3,3> & m, StaticMatrix<T,3,3> & m_inverted){
    Real e2_df = m(1,2)*m(1,2) - m(1,1)*m(2,2);  // e^2 - d*f
    Real bf = m(0,1)*m(2,2);
    Real ce = m(0,2)*m(1,2);
    Real c2 = m(0,2)*m(0,2);
    Real cd = m(0,2)*m(1,1);
    Real be = m(0,1)*m(1,2);
    Real af = m(0,0)*m(2,2);
    Real ae = m(0,0)*m(1,2);
    Real bc = m(0,1)*m(0,2);
    Real b2 = m(0,1)*m(0,1);
    Real ad = m(0,0)*m(1,1);

    Real Div = 1.0 / (c2*m(1,1) + m(0,1) * (bf - 2 * ce) +m(0,0)* e2_df  );

    Real a = e2_df * Div;
    Real b = (bf - ce) * Div;
    Real c = (cd - be) * Div;
    Real d = (c2 - af) * Div;
    Real e = (ae - bc) * Div;
    Real f = (b2 - ad) * Div;
    m_inverted(0,0)=a;
    m_inverted(0,1)=b;
    m_inverted(0,2)=c;

    m_inverted(1,0)=b;
    m_inverted(1,1)=d;
    m_inverted(1,2)=e;

    m_inverted(2,0)=c;
    m_inverted(2,1)=e;
    m_inverted(2,2)=f;
  }

  void inverse (StaticMatrix<T,3,3> inv, const StaticMatrix<T,3,3> m) const
  {
    const Matrix3x3 m=*this;
    Real a = m(0,0);
    Real b = m(0,1);
    Real c = m(0,2);
    Real d = m(1,0);
    Real e = m(1,1);
    Real f = m(1,2);
    Real g = m(2,0);
    Real h = m(2,1);
    Real i = m(2,2);
    Real Div = -c*e*g+b*f*g+c*d*h-a*f*h-b*d*i+a*e*i;
    if (fabs(Div) < EPSILON)
    {
      std::cout << "matrix inversion failed\n";
      return Matrix3x3 (Vector3D (), Vector3D (), Vector3D ());
    }
    Div = (1.0/Div);
    inv =  Matrix3x3 (	(Vector3D(-f*h+e*i,c*h-b*i,-c*e+b*f)*Div),
      (Vector3D(f*g-d*i,-c*g+a*i,c*d-a*f)*Div),
      (Vector3D(-e*g+d*h,b*g-a*h,-b*d+a*e)*Div));
    // hat Mathematica so ermittelt
  }
  */
  template<typename Vector3Type, typename Matrix3x3Type>
  inline void crossProductMatrix(Matrix3x3Type & r_star, const Vector3Type & r){
    r_star(0,0)=0; r_star(0,1)=-r(2); r_star(0,2)=r(1);
    r_star(1,0)=r(2); r_star(1,1)=0; r_star(1,2)=-r(0);
    r_star(2,0)=-r(1); r_star(2,1)=r(0); r_star(2,2)= 0;
  }

  template<typename T, typename MatrixType>
  inline MatrixType & setMatrixConstant(MatrixType & mat, const T & val){
      for(int i= 0; i < mat.rows(); i++){
          for(int j=0; j < mat.cols(); j++){
              mat(i,j)=val;
          }
      }

    return mat;
  }
}

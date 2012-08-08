#pragma once 
#include <common/Config.h>
#include <math/ScalarOperations.h>
#include <iostream>
#include <functional>

namespace nspace{
  template<typename MatA, typename MatB>
  class MatrixAssign{
  public:
    static inline void operation(MatA &  result, const MatB & val){
      if(!result.resize(val.rows(), val.cols())){
        std::cout << "MatrixAssign: could not resize result matrix "<<endl;
        return;
      }
      for(int i=0; i < result.rows(); i++){
        for(int j=0; j < result.cols(); j++){
          result(i,j)=val(i,j);
        }
      }
    }
  };
  template<typename T, typename Mat>
  class MatrixSetConstant{
  public:
    static inline void operation(Mat &  result, const T & val){
      for(int i=0; i < result.rows(); i++){
        for(int j=0; j < result.cols(); j++){
          result(i,j)=val;
        }
      }
    }
  };
  template<typename Mat, typename Func>
  class MatrixSetFunction{
  public:
    static inline void operation(Mat &  result, Func f){
      for(int i=0; i < result.rows(); i++){
        for(int j=0; j < result.cols(); j++){
          result(i,j)=f(i,j);
        }
      }
    }
  };

  template<typename Sum, typename Summand1, typename Summand2>
  class MatrixAddition{
  public:
  static inline void operation(Sum & sum, const Summand1 & a, const Summand2 & b){
    for(int i=0; i < a.rows(); i++){
      for(int j=0; j < a.cols(); j++){
        sum(i,j)=a(i,j)+b(i,j);
      }
    }
  }
  };
  
  template<typename Product, typename MatrixFactor, typename ScalarFactor>
  class MatrixMultiplyScalar{
  public:
    static inline void operation(Product & product, const MatrixFactor & a, const ScalarFactor & d){
      for(int i=0; i < a.rows(); i++){
        for(int j=0; j < a.cols(); j++){
          product(i,j)=a(i,j)*d;
        }
      }
    }
  };

  template<typename T>
  class MatrixOperations{
  public:
  template<typename MatrixType>
  static inline void transposeInPlace(MatrixType & A){
    if(A.rows()!=A.cols()){
      std::cerr << "transpose in place only works with Square Matrices"<<std::endl;
    }
    for(int i=0; i < A.rows(); i++){
      for(int j=i+1; j < A.cols(); j++){
        T tmp;
        tmp = A(i,j);
        A(i,j)=A(j,i);
        A(j,i)=tmp;
      }
    }

  }
  template<typename MatrixType>
  static inline void transpose(MatrixType & AT, const MatrixType & A){
    for(int i=0; i < A.rows(); i++){
      for(int j=0; j < A.cols(); j++){
        // the tmp var is need if AT == A
        T tmp;
        tmp = A(i,j);
        A(i,j)=A(j,i);
        A(j,i)=tmp;
      }
    }
  }
 


   /* template<typename MatrixType>
    static inline void setFunction(MatrixType & result, std::function<void (T& , int i, int j) > f ){
      for(int i=0; i < result.rows(); i++){
        for(int j=0; j < result.cols(); j++){
          f(result(i,j),i,j);
        }
      }
    }
    template<typename MatrixType>
    static inline void setConstant(MatrixType & result, const T &val){
      for(int i=0; i < result.rows(); i++){
        for(int j=0; j < result.cols(); j++){
          result(i,j)=val;
        }
      }
    }   */
    template<typename MatrixType>
    static inline void negate(MatrixType & result,const MatrixType & m){
      for(int i=0; i < result.rows(); i++){
        for(int j=0; j < result.cols(); j++){
          result(i,j)=-m(i,j);
        }
      }
    }   
    
    template<typename MatrixType>
    static inline void subtraction(MatrixType & difference, const MatrixType & a, const MatrixType & b){
      for(int i=0; i < a.rows(); i++){
        for(int j=0; j < a.cols(); j++){
          difference(i,j)=a(i,j)-b(i,j);
        }
      }
    }
    
    template<typename MatrixType>
    static inline void divideScalar(MatrixType & product, const MatrixType & a, const T & d){
      T reciproc;
      ScalarOperations<T>::reciprocal(reciproc,d);
      for(int i=0; i < a.rows(); i++){
        for(int j=0; j < a.cols(); j++){
          product(i,j)=a(i,j)*d;
        }
      }
    }
    
  };
   template<typename T, typename ProductType, typename FactorAType, typename FactorBType>
    class MatrixMultiplication{
    public:
    static inline void multiply(ProductType & product, const FactorAType & a, const FactorBType & b){
      T sum;
      const int RowCount = product.rows();
      const int ColumnCount = product.cols();
      const int InnerDimension = a.cols();
      for(int i=0; i < RowCount; i++){
        for(int j=0; j < ColumnCount; j++){
          sum=0;
          //ScalarOperations<T>::Zero(sum);
          for(int k=0; k < InnerDimension;k++){
            sum+=a(i,k)*b(k,j);
            /*ScalarOperations<T>::multiply(scalarProduct,a(i,k),b(k,j));
            ScalarOperations<T>::add(sum,sum,scalarProduct);*/
          }
          product(i,j)=sum;
        }
      }
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
    MatrixOperations<T>::setConstant<MatrixType>(mat,val);
    return mat;
  }
}
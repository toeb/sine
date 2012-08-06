#include <common/Config.h>

#include <math/ScalarOperations.h>
#include <math/definitions.h>
#include <iostream>
#include <functional>

namespace nspace{

  
  template<typename T>
  class MatrixOperations{
  public:
  
    template<typename MatrixType>
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
    }
    

    template<typename MatrixType>
    static inline void addition(MatrixType & sum, const MatrixType & a, const MatrixType & b){
      for(int i=0; i < a.rows(); i++){
        for(int j=0; j < a.cols; j++){
          sum(i,j)=a(i,j)+b(i,j);
        }
      }
    }
    template<typename MatrixType>
    static inline void subtraction(MatrixType & difference, const MatrixType & a, const MatrixType & b){
      for(int i=0; i < a.rows(); i++){
        for(int j=0; j < a.cols; j++){
          sum(i,j)=a(i,j)+b(i,j);
        }
      }
    }
    template<typename MatrixType>
    static inline void multiply(MatrixType & product, const MatrixType & a, const T & d){
      for(int i=0; i < a.rows(); i++){
        for(int j=0; j < a.cols; j++){
          product(i,j)=a(i,j)*d;
        }
      }
    }
    template<typename ProductType, typename FactorAType, typename FactorBType>
    class MatrixProduct{
    public:
      static inline void multiply(ProductType & product, const FactorAType & a, const FactorBType & b){
        T sum;
        T scalarProduct;
        const int RowCount = product.rows();
        const int ColumnCount = product.cols();
        const int InnerDimension = a.cols();
        for(int i=0; i < RowCount; i++){
          for(int j=0; j < ColumnCount; j++){
            ScalarOperations<T>::Zero(sum);
            for(int k=0; k < InnerDimension;k++){
              ScalarOperations<T>::multiply(scalarProduct,a(i,k),b(k,j));
              ScalarOperations<T>::add(sum,sum,scalarProduct);
            }
            product(i,j)=sum;
          }
        }
      }
    };
    

    
  };

  

  
  template<typename T, typename MatrixType>
  inline MatrixType & setMatrixConstant(MatrixType & mat, const T & val){
    MatrixOperations<T>::setConstant<MatrixType>(mat,val);
    return mat;
  }
}
#pragma once
#include <math/MatrixOperations.h>
#include <math/VectorOperations.h>
#include <math/matrix2/StaticMatrixSpecialization.h>
namespace nspace{
  namespace matrix2{

  template<typename T,int rows, int cols>
  inline std::ostream &  operator<<(std::ostream &  s, const matrix2::StaticMatrix<T,rows,cols> & a){
    for(int i=0; i < a.rows(); i++){
      for(int j=0; j < a.cols(); j++){
        s << a(i,j)<<", ";
      }
      s << "\n";
    }
    return s;
  }
  template<typename T,int rows, int cols>
  inline matrix2::StaticMatrix<T,rows,cols> operator+(const matrix2::StaticMatrix<T,rows,cols> & a,const matrix2::StaticMatrix<T,rows,cols> & b){
    matrix2::StaticMatrix<T,rows,cols> c;
    MatrixAddition<StaticMatrix<T,rows,cols>,StaticMatrix<T,rows,cols>,StaticMatrix<T,rows,cols> >::operation(c,a,b);
    return c;
  }

  template<typename T>
  inline matrix2::StaticMatrix<T,3,1> operator^(const matrix2::StaticMatrix<T,3,1> & a,const matrix2::StaticMatrix<T,3,1> & b){
    matrix2::StaticMatrix<T,3,1> c;
    VectorOperations<T>::crossProduct(c,a,b);
    return c;
  }


  template<typename T, int dimension>
  inline T operator*(const matrix2::StaticMatrix<T,dimension,1> & a,const matrix2::StaticMatrix<T,dimension,1> & b){
    T result;
   VectorOperations<T>::innerProduct(result,a,b);
    return result;
  }

  template<typename T,int rows, int cols>
  inline  matrix2::StaticMatrix<T,rows,cols> operator-(const matrix2::StaticMatrix<T,rows,cols> & a,const matrix2::StaticMatrix<T,rows,cols> & b){
    matrix2::StaticMatrix<T,rows,cols> c;
    MatrixOperations<T>::subtraction(c,a,b);
    return c;
  }
  template<typename T,int rows, int cols>
  inline  matrix2::StaticMatrix<T,rows,cols> operator*(const matrix2::StaticMatrix<T,rows,cols> & a, const T & d){
    matrix2::StaticMatrix<T,rows,cols> c;
    MatrixMultiplyScalar<matrix2::StaticMatrix<T,rows,cols>,matrix2::StaticMatrix<T,rows,cols>,T>::operation(c,a,d);
    return c;
  }
  template<typename T,int rows, int cols>
  inline  matrix2::StaticMatrix<T,rows,cols> operator/(const matrix2::StaticMatrix<T,rows,cols> & a, const T & d){
    matrix2::StaticMatrix<T,rows,cols> c;
    MatrixOperations<T>::divideScalar(c,a,d);
    return c;
  }
  template<typename T,int rows, int cols>
  inline  matrix2::StaticMatrix<T,rows,cols> operator*(const T & d,const matrix2::StaticMatrix<T,rows,cols> & a){
    matrix2::StaticMatrix<T,rows,cols> c;
    MatrixMultiplyScalar<matrix2::StaticMatrix<T,rows,cols>,matrix2::StaticMatrix<T,rows,cols>,T>::operation(c,a,d);
    return c;
  }
  template<typename T, int outerRows, int outerCols, int innerDimension>
  inline matrix2::StaticMatrix<T,outerRows,outerCols> operator * (const matrix2::StaticMatrix<T,outerRows,innerDimension> & a,const matrix2::StaticMatrix<T,innerDimension,outerCols> & b){
    matrix2::StaticMatrix<T,outerRows,outerCols> c;
    MatrixMultiplication<T, matrix2::StaticMatrix<T,outerRows,outerCols>,matrix2::StaticMatrix<T,outerRows,innerDimension>,matrix2::StaticMatrix<T,innerDimension,outerCols>>::multiply(c,a,b);
    return c;
  };

  template<typename T, int rows, int cols> 
  inline StaticMatrix<T,rows,cols> & operator +=(StaticMatrix<T,rows,cols> & a, const StaticMatrix<T,rows,cols> & b ){
    MatrixAddition<StaticMatrix<T,rows,cols>,StaticMatrix<T,rows,cols>, StaticMatrix<T,rows,cols> >::operation(a,a,b);
    return a;
  }
  template<typename T, int rows, int cols> 
  inline StaticMatrix<T,rows,cols> & operator -=(StaticMatrix<T,rows,cols> & a, const StaticMatrix<T,rows,cols> & b ){
    MatrixOperations<T>::subtraction(a,a,b);
    return a;
  }
  template<typename T, int rows, int cols> 
  inline StaticMatrix<T,rows,cols> & operator *=(StaticMatrix<T,rows,cols> & a, const T & d){
    MatrixOperations<T>::multiplyScalar(a,a,d);
    return a;
  }
  template<typename T, int rows, int cols>
  inline StaticMatrix<T,rows,cols> & operator /=(StaticMatrix<T,rows,cols> & a, const T & d){
    MatrixOperations<T>::divideScalar(a,a,d);
    return a;
  }


}
}
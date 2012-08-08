#pragma once
#include <math/Matrix.h>
#include <common/patterns/ArrayPool.h>
#include <math/MatrixOperations.h>
namespace nspace{
  namespace matrix2{
template<typename T>
class DynamicMatrix  : public nspace::Matrix<T>{
protected:
  T * _data;
  int _rows;
  int _cols;
  inline Real & value(int i, int j){
    return _data[index(i,j)];
  }
  inline const Real & value(int i, int j)const{
    return _data[index(i,j)];
  }
public:
  inline void setConstant(const T & val){
    MatrixSetConstant<T, DynamicMatrix<T> >::operation(*this,val);
  }
  inline void setFunction(std::function<void (T& ,int,int)> f){
    MatrixSetFunction<DynamicMatrix<T> ,std::function<void (T& ,int,int)> >::operation(*this,f);
  }
  inline void setZero(){
    MatrixSetConstant<T, DynamicMatrix<T> >::operation(*this,0.0);
    //memset(_data,0,dataByteSize());
  }
  inline void assign(const DynamicMatrix & mat){
    MatrixAssign<DynamicMatrix<T>,DynamicMatrix<T> >::operation(*this,mat);
  }
  inline T norm()const{
    T result;
    VectorOperations<T>::norm(result,*this);
    return result;
  }

  DynamicMatrix(const DynamicMatrix<T> & orig):_data(0),_rows(0),_cols(0){
    assign(orig);
  }
  inline int size()const{
    return _rows*_cols;
  }
  ~DynamicMatrix(){
    ArrayPool<T>::freeArray(&_data,size());
    _rows = 0;
    _cols = 0;
  }
  DynamicMatrix():_rows(0),_cols(0),_data(0){resize(0,0);};
  inline size_t dataByteSize()const{
    return _rows*_cols*sizeof(T);
  }
  inline DynamicMatrix<T> & operator=(const DynamicMatrix<T> & orig ){
    assign(orig);
    return *this;
  }
  inline bool resize(int n, int m, bool setToZero=true){
    if(_rows==n && _cols==m)return true; 

    ArrayPool<T>::freeArray(&_data,size());
    _rows = n;
    _cols=m;
    ArrayPool<T>::createArray(&_data,size());

    _rows = n;
    _cols =m;
    if(setToZero) setZero();
    return true;
  }
  inline Real * rowData(int i){
    return _data +(i*_cols);
  }
  inline int index(int i, int j)const{return i* _cols+j;}
  inline T & operator()(int i, int j){return _data[i* _cols+j]; }
  inline const T & operator()(int i, int j)const{return _data[i* _cols+j]; }
  inline T & operator()(int i){return _data[i]; }
  inline const T & operator()(int i)const{return _data[i]; }
  inline int rows()const{return _rows;}
  inline int cols()const{return _cols;}
  T * data(){return _data;}
  const T * data()const{return _data;}
};

template<typename T>
inline DynamicMatrix<T>  operator * (const DynamicMatrix<T> & a, const DynamicMatrix<T> & b){
  DynamicMatrix<T> result;
  result.resize(a.rows(),b.cols());
  MatrixMultiplication<T,DynamicMatrix<T>,DynamicMatrix<T>,DynamicMatrix<T>>::multiply(result,a,b);
  return result;
}
template<typename T>
inline DynamicMatrix<T>  operator *= (DynamicMatrix<T> & a, const T & b){
  MatrixOperations<T>::multiplyScalar(a,a,b);
  return a;
}
template<typename T>
inline DynamicMatrix<T>  operator * (const DynamicMatrix<T> & a, const T & b){
  DynamicMatrix<T> result;
  result.resize(a.rows(),a.cols());
  MatrixMultiplyScalar<DynamicMatrix<T>,DynamicMatrix<T>,T>::operation(result,a,b);
  return result;
}
template<typename T>
inline DynamicMatrix<T>  operator / (const DynamicMatrix<T> & a, const T & b){
  DynamicMatrix<T> result;
  result.resize(a.rows(),a.cols());
  MatrixOperations<T>::divideScalar(result,a,b);
  return result;
}
template<typename T>
inline DynamicMatrix<T>  operator * (const T & b,const DynamicMatrix<T> & a){
  DynamicMatrix<T> result;
  result.resize(a.rows(),a.cols());
  MatrixMultiplyScalar<DynamicMatrix<T>,DynamicMatrix<T>,T>::operation(result,a,b);
  return result;
}
template<typename T>
inline DynamicMatrix<T> & operator += (DynamicMatrix<T> & a, const DynamicMatrix<T> & b){
  MatrixAddition<DynamicMatrix<T>,DynamicMatrix<T>, DynamicMatrix<T> >::operation(a,a,b);
  return a;
}
template<typename T>
inline DynamicMatrix<T>  operator + (const DynamicMatrix<T> & a, const DynamicMatrix<T> & b){
  DynamicMatrix<T> result; 
  MatrixAddition<DynamicMatrix<T>,DynamicMatrix<T>, DynamicMatrix<T> >::operation(result,a,b);
  return result;
}
template<typename T>
inline DynamicMatrix<T>  operator - (const DynamicMatrix<T> & a, const DynamicMatrix<T> & b){
  DynamicMatrix<T> result;
  result.resize(a.rows(),a.cols());
  MatrixOperations<T>::subtraction(result,a,b);
  return result;
}

template<typename T>
inline DynamicMatrix<T> & operator -= (DynamicMatrix<T> & a, const DynamicMatrix<T> & b){
  MatrixOperations<T>::subtraction(a,a,b);
}





  }//endof of matrix2
  //dynamic matrix specialization
  template<typename T>
  class MatrixAddition<matrix2::DynamicMatrix<T>, matrix2::DynamicMatrix<T>, matrix2::DynamicMatrix<T> >{
  public: 
    static inline void operation(matrix2::DynamicMatrix<T> & sumMat,const matrix2::DynamicMatrix<T> & aMat, const matrix2::DynamicMatrix<T> & bMat){
      int rows = aMat.rows();
      int cols = bMat.cols();
      if(bMat.rows()!=rows ||bMat.cols()!=cols){
        std::cerr << "matrix addition failed. dimension mismatch"<<std::endl;
        return;
      }
      int size = rows*cols;
      sumMat.resize(rows,cols,false);
      // get data arrays
      const T* a=aMat.data();
      const T* b = bMat.data();
      T* c=sumMat.data();


      #pragma omp parallel for
      for(int i=0; i < size; ++i){
        c[i]=a[i]+b[i];
      }
    }
  } ;
  template<typename T>
  class MatrixSetConstant<T,matrix2::DynamicMatrix<T> >{
  public:
    static inline void operation(matrix2::DynamicMatrix<T> & target, const T & value){
      Real * t =target.data();
      const int s = target.size();
      //go serial if size is smaller than sum trehshold
      if(s < 1000){
        for(int i=0; i < s; i++){
          t[i]=value;
        }
        return ; 
      }
      //go parallel 
      #pragma omp parallel for
      for(int i=0; i < s; i++){
        t[i]=value;
      }

    }
  };

  template<typename T>
  class MatrixSetFunction<matrix2::DynamicMatrix<T> , std::function<void (T & val, int i, int j)> >{
  public:
    static inline void operation(matrix2::DynamicMatrix<T> & target, std::function<void (T & val, int i, int j)> f ){
      T * t =target.data();
      const int s = target.size();
      const int rows = target.rows();
      const int cols = target.cols();
      //go serial if size is smaller than sum trehshold
      if(s < 1000){
        for(int i=0; i < s; i++){
          f(t[i], i/cols, i%cols);
        }
        return ; 
      }
      //go parallel 
#pragma omp parallel for
      for(int i=0; i < s; i++){
        f(t[i], i/cols, i%cols);
      }

    }
  };

  template<typename T>
  class MatrixMultiplyScalar<matrix2::DynamicMatrix<T>,matrix2::DynamicMatrix<T>,T>{
  public:
    static inline void operation(matrix2::DynamicMatrix<T> & cMat, const matrix2::DynamicMatrix<T> & aMat, const T & b){
      const int s = aMat.size();
      cMat.resize(aMat.rows(),aMat.cols(),false);
      const T * a = aMat.data();
      T * c = cMat.data();
      //go serial if size is smaller than sum trehshold
      if(s < 1000){
        for(int i=0; i < s; i++){
          c[i]=b*a[i];
        }
        return ; 
      }
      //go parallel 
      #pragma omp parallel for
      for(int i=0; i < s; i++){
        c[i]=b*a[i];
      }

    }
  };

  template<typename T>
  class MatrixAssign<matrix2::DynamicMatrix<T>, matrix2::DynamicMatrix<T> >{
  public:
    static inline void operation(matrix2::DynamicMatrix<T> &  result, const matrix2::DynamicMatrix<T> & val){
      const int rows = val.rows();
      const int cols = val.cols();
      result.resize(rows,cols,false);
      T * a = result.data();
      const T * b = val.data();
      const int size = rows*cols;
      if(size < 20000){
        memcpy(a,b,result.dataByteSize());
        return;
      }
      
      #pragma omp parallel for
      for(int i=0; i < size; i++){
        a[i] = b[i];
      }
    }
  };

}
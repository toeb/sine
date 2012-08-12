#pragma once

#include <math/matrix2/DynamicMatrix.h>
namespace nspace{

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
  class MatrixSubtraction<matrix2::DynamicMatrix<T>, matrix2::DynamicMatrix<T>, matrix2::DynamicMatrix<T> >{
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
        c[i]=a[i]-b[i];
      }
    }
  } ;

  template<typename T>
  class MatrixSetConstant<T,matrix2::DynamicMatrix<T> >{
  public:
    static inline void operation(matrix2::DynamicMatrix<T> & target, const T & value){
      if(value==0.0){
        memset(target.data(),0,target.dataByteSize());
        return;
      }
      T * t =target.data();
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
  class MatrixScalarMultiplication<matrix2::DynamicMatrix<T>,matrix2::DynamicMatrix<T>,T>{
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


  template<typename T>
  class MatrixExtractBlock<matrix2::DynamicMatrix<T>, matrix2::DynamicMatrix<T> >{
  public:
    static inline void operation(matrix2::DynamicMatrix<T> & result, const matrix2::DynamicMatrix<T> & original, uint startRow, uint startCol, uint rows, uint cols){

      uint srcCols = original.cols();
      uint srcRows = original.rows();
      if(startRow + rows > srcRows){

        std::cerr << __FUNCSIG__ << " rows out of range"<<std::endl;
        return;
      }
      if(startCol+ cols>srcCols){
        std::cerr << __FUNCSIG__ << " cols out of range"<<std::endl;
        return;
      }
      result.resize(rows,cols,false);
      const Real * src = original.data();
      Real * dst = result.data();
      size_t length=sizeof(T)*cols;
      const  Real * srcOffset = src+ startRow * srcCols;
      
      for(uint i=0; i < rows; i++){
        memcpy(dst+i*cols,srcOffset+i*srcCols,length); //saved one operation
        //memcpy(dst+i*cols,src+(startRow+i)*(srcCols),length);
      }
    }
  };


  

  template<typename KernelMatrix,typename T>
  class MatrixConvolution<matrix2::DynamicMatrix<T>,matrix2::DynamicMatrix<T>,KernelMatrix,T>{
  public:
    static inline void operation(matrix2::DynamicMatrix<T> & rMat, const matrix2::DynamicMatrix<T> & gMat, const KernelMatrix & kernel  ){
      uint fx = kernel.cols();
      uint fy = kernel.rows();
      uint rx = gMat.cols()-fx+1;
      uint ry = gMat.rows()-fy+1;
      uint rCols = rMat.cols();
      uint gCols = gMat.cols();
      rMat.resize(ry,rx);
      Real * r = rMat.data();
      const Real* g =gMat.data();

      Real * f =new Real[kernel.size()];

      for(int i=0; i< kernel.size(); i++)f[i]=kernel(i);
      const Real * gOffset;
      const Real * fOffset;
//#pragma omp parallel for
      for(int i=0; i < ry; i++){
        for(int j=0; j < rx; j++){
          T  sum=0.0;          
          
          for(int l = 0; l < fy; ++l){
            gOffset = g+(i+l)*gCols+j;
            fOffset = f+ l*fx;
            for(int k =0; k < fx; ++k){
              sum = sum + gOffset[k]*fOffset[k];
            }
          }
          //r(i,j)=sum;
          r[i*rCols+j]=sum;
        }
      }

      delete f;
    }
  };

}
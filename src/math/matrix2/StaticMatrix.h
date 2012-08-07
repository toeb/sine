#pragma once
#include <math/Matrix.h>
#include <queue>
#include <math/VectorOperations.h>
#include <math/MatrixOperations.h>
namespace nspace{
  namespace matrix2{
template<typename T, int RowCount, int ColumnCount>
class StaticMatrix : public Matrix<T>{
protected:
  T _data[RowCount*ColumnCount];
  inline Real & value(int i, int j){
    return _data[index(i,j)];
  }
  inline const Real & value(int i, int j)const{
    return _data[index(i,j)];
  }

public:
  inline static const StaticMatrix<T,RowCount,ColumnCount> & Zero(){
    
    return _zeroMatrix;
  }
  //rule of three
  StaticMatrix(const StaticMatrix<T,RowCount,ColumnCount> & orig){
    *this=orig;
  }
  StaticMatrix<T,RowCount,ColumnCount> & operator=(const StaticMatrix<T,RowCount,ColumnCount> & orig ){
    memcpy(data(),orig.data(),dataByteSize());
    return *this;
  }
  StaticMatrix(){}
  ~StaticMatrix(){}
  inline size_t dataByteSize()const{
    return RowCount*ColumnCount*sizeof(T);
  }
  inline int index(int i, int j)const{return i* ColumnCount+j;}

  inline T & operator()(int i, int j){return _data[i* ColumnCount+j]; }
  inline T & operator()(int i){return _data[i];}
  inline const T & operator()(int i)const{return _data[i];}
  inline const T & operator()(int i, int j)const{return _data[i* ColumnCount+j]; }
  inline int rows()const{return RowCount;}
  inline int cols()const{return ColumnCount;}
  T * data(){return &_data[0];}
  const T * data()const{return &_data[0];}    
  inline void assign(const T * dataPtr){
    memcpy(_data, dataPtr,dataByteSize());
  }
  inline void copyTo(T * dataPtr)const{
    memcpy(dataPtr,_data,dataByteSize());
  }
  inline void setZero(){
    memset(_data,0,dataByteSize());
  }
  
  //inline StaticMatrix<T,1,ColumnCount> row(int i);
  StaticMatrix(const T& x,const T& y,const T& z){
    _data[0]=x;
    _data[1]=y;
    _data[2]=z;
  }
  static const StaticMatrix<T,3,1> & UnitX(){
    static StaticMatrix<T,3,1> _unitXVector(1,0,0);
    return _unitXVector;
  }
  static const StaticMatrix<T,3,1> & UnitY(){
    static StaticMatrix<T,3,1> _unitYVector(0,1,0);
    return _unitYVector;
  }
  static const StaticMatrix<T,3,1> & UnitZ(){
    static StaticMatrix<T,3,1> _unitZVector(0,0,1);
    return _unitZVector;
  }
  static const StaticMatrix<T,RowCount,ColumnCount> & Ones(){
    static StaticMatrix<T,RowCount,ColumnCount> _unitZVector(0,0,1);
    return _unitZVector;
  }
  

  inline T & x(){return _data[0];}
  inline const T & x()const{return _data[0];} 
  inline T & y(){return _data[1];}
  inline const T & y()const{return _data[1];} 
  inline T & z(){return _data[2];}
  inline const T & z()const{return _data[2];} 
  inline T & w(){return _data[3];}
  inline const T & w()const{return _data[3];} 
  StaticMatrix(const T& w,const T& x,const T& y,const T& z){
    _data[0]=x;
    _data[1]=y;
    _data[2]=z;
    _data[3]=w;

  }
  static const StaticMatrix<T,4,1> & ZeroRotation(){
    static StaticMatrix<T,4,1> _zeroRotationVector(1,0,0,0);
    return _zeroRotationVector;
  }



  inline T length()const{
    T result;
    VectorOperations<T>::norm(result,*this);
    return result;
  }
  inline T norm()const{
    T result;
    VectorOperations<T>::norm(T,*this);
    return result;
  }
  inline T length2()const{
    T result;
    VectorOperations<T>::normSquared(T,*this);
    return result;
  }
  inline T norm2()const{
    T result;
    VectorOperations<T>::normSquared(T,*this);
    return result;
  }
  inline T maximum()const{
    T result;
    VectorOperations<T>::maximum(result,*this);
    return result;
  }
  inline T minimum()const{
    T result;
    VectorOperations<T>::minimum(result,*this);
  }
  inline void normalize(){
    VectorOperations<T>::normalize(*this);
  }

private :

  class Initializer{
  public:
    Initializer(){
      _zeroMatrix.setZero();
      for(int i=0; i <_onesMatrix.size(); i++)_onesMatrix._data[i]=1;
    }
  };
  Initializer init;
  static StaticMatrix<T,RowCount,ColumnCount> _zeroMatrix;
  static StaticMatrix<T,RowCount,ColumnCount> _onesMatrix;
};
  }
}
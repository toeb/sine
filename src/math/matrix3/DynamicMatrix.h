#pragma once
#include <math/Matrix.h>
#include <common/patterns/ArrayPool.h>

namespace nspace{
  namespace matrix3{
template<typename T>
class  DynamicMatrix : public Matrix<T>{
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

  DynamicMatrix(const DynamicMatrix<T> & orig):_data(0),_rows(0),_cols(0){
    *this=orig;
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
    resize(orig.rows(),orig.cols(),false);
    memcpy(data(),orig.data(),dataByteSize());
    return *this;
  }
  void resize(int n, int m, bool setToZero=true){
    if(_rows==n && _cols==m)return;

    ArrayPool<T>::freeArray(&_data,size());
    _rows = n;
    _cols=m;
    ArrayPool<T>::createArray(&_data,size());

    _rows = n;
    _cols =m;
    if(setToZero) memset(_data,0,dataByteSize());
  }
  inline Real * rowData(int i){
    return _data +(i*_cols);
  }
  inline int index(int i, int j)const{return i* _cols+j;}
  inline T & operator()(int i, int j){return _data[i* _cols+j]; }
  inline const T & operator()(int i, int j)const{return _data[i* _cols+j]; }

  inline int rows()const{return _rows;}
  inline int cols()const{return _cols;}
  T * data(){return _data;}
  const T * data()const{return _data;}
};
}
}
#pragma once
#include <math/Matrix.h>
#include <core/patterns/ArrayPool.h>

namespace nspace{
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

  DynamicMatrix(const DynamicMatrix<T> & orig):_data(0),_rows(0),_cols(0){
    *this=orig;
  }

  ~DynamicMatrix(){
    nspace::ArrayPool<T>::freeArray(&_data,this->size());
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
  bool resize(int n, int m, bool setToZero=true){
    if(_rows==n && _cols==m)return true;

    nspace::ArrayPool<T>::freeArray(&_data,this->size());
    _rows = n;
    _cols=m;
    nspace::ArrayPool<T>::createArray(&_data,this->size());

    _rows = n;
    _cols =m;
    if(setToZero) memset(_data,0,dataByteSize());
    return true;
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

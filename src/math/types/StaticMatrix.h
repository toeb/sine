#pragma once
#include <math/types/Matrix.h>
namespace nspace{
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
  inline T & operator()(int i, int j){return _data[index(i,j)]; }
  inline const T & operator()(int i, int j)const{return _data[index(i,j)]; }
  inline int rows()const{return RowCount;}
  inline int cols()const{return ColumnCount;}
  T * data(){return &_data[0];}
  const T * data()const{return &_data[0];}    
};
}
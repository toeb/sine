#pragma once
#include <math/Matrix.h>
#include <math/VectorOperations.h>
#include <math/MatrixOperations.h>
#include <queue>
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

  inline static StaticMatrix<T,RowCount,ColumnCount>  Zero(){    
    StaticMatrix<T,RowCount,ColumnCount>  matrix;    
    matrix.setZero();          
    return matrix;
  }
  //rule of three
  StaticMatrix(const StaticMatrix<T,RowCount,ColumnCount> & orig){
    *this=orig;
  }
  StaticMatrix(const T& x, const T& y){
    _data[0]=x;
    _data[1]=y;
  }
  StaticMatrix(const Real * dataPtr){
    assign(dataPtr);
  }
  inline StaticMatrix<T,RowCount,ColumnCount> & operator=(const StaticMatrix<T,RowCount,ColumnCount> & orig ){
    MatrixAssign<StaticMatrix<T,RowCount,ColumnCount>,StaticMatrix<T,RowCount,ColumnCount> >::operation(*this,orig);
    //memcpy(_data,orig._data,dataByteSize());
    return *this;
  }
  StaticMatrix(){}
  ~StaticMatrix(){}
  inline size_t dataByteSize()const{
    return RowCount*ColumnCount*sizeof(T);
  }
  inline int index(int i, int j)const{return i* ColumnCount+j;}

  
  StaticMatrix<T,ColumnCount,1> row(int i)const{
    StaticMatrix<T,ColumnCount,1> result;
    result.assign(getRow(i));
  }
  StaticMatrix<T,RowCount,1>col(int j)const{
    StaticMatrix<T,RowCount,1> result;
    for(int i=0; i < RowCount;i++ ){
      result(i)=value(i,j);
    }
    return result;
  }

  inline const T * getRow(int index)const{
    return _data+index*ColumnCount;
  }

  inline T & operator()(int i, int j){return _data[i* ColumnCount+j]; }
  inline T & operator()(int i){return _data[i];}
  inline const T & operator()(int i)const{
    return _data[i];
  }
  inline const T & operator()(int i, int j)const{return _data[i* ColumnCount+j]; }
  inline int rows()const{return RowCount;}
  inline int cols()const{return ColumnCount;}
  T * data(){return &_data[0];}
  const T * data()const{return &_data[0];}    
  inline void assign(const T * dataPtr){
    memcpy(_data, dataPtr,dataByteSize());
  }
  inline bool isZero(const Real epsilon = EPSILON)const{
    bool result;
    MatrixIsZero<StaticMatrix<T, RowCount, ColumnCount>::(result, *this, epsilon);
    return result;
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
  static StaticMatrix<T,RowCount,ColumnCount> Ones(){
    StaticMatrix<T,RowCount,ColumnCount> matrix;
    matrix.setZero();
    for(int i=0; i < RowCount; i++)
      for(int j=0; j < ColumnCount; j++)
        matrix(i,j)=1;
    return matrix;    
  }
  

  inline T & x(){return _data[0];}
  inline const T & x()const{return _data[0];} 
  inline T & y(){return _data[1];}
  inline const T & y()const{return _data[1];} 
  inline T & z(){return _data[2];}
  inline const T & z()const{return _data[2];} 
  inline T & w(){return _data[3];}
  inline const T & w()const{return _data[3];} 
  StaticMatrix(const T& x,const T& y,const T& z,const T& w){
    _data[0]=x;
    _data[1]=y;
    _data[2]=z;
    _data[3]=w;
  }
  static StaticMatrix<T,RowCount,ColumnCount> Identity(){
    StaticMatrix<T,RowCount,ColumnCount> matrix;    
    matrix.setZero();
    for(int i=0; i < RowCount && i < ColumnCount; i++){
      matrix(i,i)=1;
    }    
    return matrix;
  }
  
  inline void transpose(){
    if(RowCount!=ColumnCount){
      std::cerr << "cannot transpose non square StaticMatrix in place" << std::endl;
    }
    MatrixTransposeInPlace<StaticMatrix<T,RowCount,ColumnCount> >::operation(*this);
  }
  inline void toTransposed(StaticMatrix<T,ColumnCount,RowCount> & AT)const{
    MatrixTranspose<StaticMatrix<T,ColumnCount,RowCount>, StaticMatrix<T,RowCount,ColumnCount> >::operation(AT,*this);
    MatrixOperations<T>::transpose(AT,*this);
  }
  inline StaticMatrix<T,ColumnCount,RowCount> transposed()const{
    StaticMatrix<T,ColumnCount,RowCount> AT;
     MatrixTranspose<StaticMatrix<T,ColumnCount,RowCount>, StaticMatrix<T,RowCount,ColumnCount> >::operation(AT,*this);
    return AT;
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
    VectorOperations<T>::normSquared(result,*this);
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
  inline bool resize(int rows, int cols, bool setToZero){
    if(rows==RowCount && cols == ColumnCount)return true;
    return false;
  }
  inline StaticMatrix<T,RowCount,ColumnCount> operator -(){
    StaticMatrix<T,RowCount,ColumnCount> result;
    MatrixOperations<T>::negate(result, *this);
    return result;
  }



};

}                                                                                                                      
}                                                                                                                        
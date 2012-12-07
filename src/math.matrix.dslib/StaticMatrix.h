#pragma once
#include <math.matrix/Matrix.h>
#include <math.matrix/VectorOperations.h>
#include <math.matrix/MatrixOperations.h>
#include <queue>

namespace nspace{
namespace matrix2{



template<typename T, int RowCount, int ColumnCount>
class StaticMatrix : public Matrix<T>{
protected:
  //< the static data array
  T _data[RowCount*ColumnCount];

  // access read/write and read access to the values of the data array
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

  
  StaticMatrix<T,ColumnCount,1> row(uint i)const{
    StaticMatrix<T,ColumnCount,1> result;
    result.assign(getRow(i));
    return result;
  }
  StaticMatrix<T,RowCount,1>col(uint j)const{
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
    matrix::compareMatrix(result,*this,StaticMatrix<T,RowCount,ColumnCount>::Zero() );
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
  //convert this matrix to any other type
  /*
  template<typename MatType>
inline operator MatType()const{
  MatType other;
  other.resize(rows(),cols());
  for(int i=0; i< rows(); i++){
    for(int j =0; j < cols(); j++){
      other(i,j)=(*this)(i,j);
    }
  }
  return other;
}*/
  
  inline T & w(){return _data[0];}
  inline const T & w()const{return _data[0];} 
  inline T & x(){return RowCount==4?_data[1]:_data[0];}
  inline const T & x()const{return RowCount==4?_data[1]:_data[0];} 
  inline T & y(){return RowCount==4?_data[2]:_data[1];}
  inline const T & y()const{return RowCount==4?_data[2]:_data[1];} 
  inline T & z(){return RowCount==4?_data[3]:_data[2];}
  inline const T & z()const{return RowCount==4?_data[3]:_data[2];} 
  StaticMatrix(const T& w,const T& x,const T& y,const T& z){
    _data[0]=w;
    _data[1]=x;
    _data[2]=y;
    _data[3]=z;
  }

  
  // access to identity matrix
  static const StaticMatrix<T,RowCount,ColumnCount> & Identity(){
    static StaticMatrix<T,RowCount,ColumnCount> * matrix=0;
    if(!matrix){
      matrix = new StaticMatrix<T,RowCount,ColumnCount>();
      matrix->setZero();
      for(uint i=0; i < RowCount && i < ColumnCount;i++) (*matrix)(i,i)=1.0;
    }    
    return *matrix;
  }
  // access to zero matrix
  inline static const StaticMatrix<T,RowCount,ColumnCount> & Zero(){
    static StaticMatrix<T,RowCount,ColumnCount> *  matrix=0;
    if(!matrix){
        matrix = new StaticMatrix<T,RowCount,ColumnCount>();
        matrix->setZero();
    }
    return *matrix;
  }
  
  inline void transpose(){
    if(RowCount!=ColumnCount){
      std::cerr << "cannot transpose non square StaticMatrix in place" << std::endl;
    }
    MatrixTransposeInPlace<StaticMatrix<T,RowCount,ColumnCount> >::operation(*this);
  }
  inline void toTransposed(StaticMatrix<T,ColumnCount,RowCount> & AT)const{
    MatrixTranspose<StaticMatrix<T,ColumnCount,RowCount>, StaticMatrix<T,RowCount,ColumnCount> >::operation(AT,*this);
    //MatrixOperations<T>::transpose(AT,*this);
  }
  inline StaticMatrix<T,ColumnCount,RowCount> transposed()const{
    StaticMatrix<T,ColumnCount,RowCount> AT;
     MatrixTranspose<StaticMatrix<T,ColumnCount,RowCount>, StaticMatrix<T,RowCount,ColumnCount> >::operation(AT,*this);
    return AT;
  }
  
  inline T length()const{
    T result;
    vectorop::norm(result,*this);
    return result;
  }
  inline T norm()const{
    T result;
    vectorop::norm(result,*this);
    return result;
  }
  inline T length2()const{
    T result;
    vectorop::normSquared(result,*this);
    return result;
  }
  inline T squaredNorm()const{
    T result;
    vectorop::normSquared(result,*this);
    return result;
  }
  inline T maximum()const{
    T result;
    vectorop::maximum(result,*this);
    return result;
  }
  inline T minimum()const{
    T result;
    vectorop::minimum(result,*this);
  }
  inline void normalize(){
    vectorop::normalize(*this);
  }
  
  inline bool resize(int rows, int cols){
    if(rows==RowCount && cols == ColumnCount)return true;    
    return false;
  }
  inline StaticMatrix<T,RowCount,ColumnCount> operator -(){
    StaticMatrix<T,RowCount,ColumnCount> result;
    math::shorthands::matrix::negate(result,*this);
    return result;
  }
};




}                                                                                                                      
}                                                                                                                        

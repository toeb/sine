#pragma once
#include <core/patterns/ArrayPool.h>

#include <math/Matrix.h>

#include <math/MatrixOperations.h>
#include <math/VectorOperations.h>
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

  inline void toUnitInterval(){
    Real mini = minimum();
    *this -= mini;
    Real maxim = maximum();
    *this /= maxim;

  }

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
  inline void assign(const DynamicMatrix<T> & mat){
    MatrixAssign<DynamicMatrix<T>,DynamicMatrix<T> >::operation(*this,mat);
  }
  template<typename SourceType>
  inline void assign(const DynamicMatrix<SourceType> & mat){
    MatrixAssign<DynamicMatrix<T>,DynamicMatrix<SourceType> >::operation(*this,mat);
  }
  template<typename TargetType>
  inline void copyTo(DynamicMatrix<TargetType> & target)const{
    target.assign(*this);
  }
  template<typename TSource>
  inline void assign(const TSource * data){
    for(int i=0; i< size();i++){
      _data[i]=data[i];
    }
  }
  template<typename Converter, typename TSource>
  inline void assign(const TSource * data){
    for(int i=0; i< size();i++){
      _data[i]=(T)(Converter)data[i];
    }
  }

  inline void filter(DynamicMatrix<T> &out,std::function<void (T & ,DynamicMatrix<T> & ) >f, uint filterWidth, uint filterHeight )const{
    MatrixFilter<DynamicMatrix<T>,DynamicMatrix<T>,std::function<void (T & ,DynamicMatrix<T> & ) >,DynamicMatrix<T>>::operation(out,*this,f,filterWidth,filterHeight);
  }
  inline DynamicMatrix<T>  filter(std::function<void (T & ,DynamicMatrix<T> & ) >f,uint filterWidth,uint filterHeight){
    DynamicMatrix<T> result;
    filter(result, f,filterWidth,filterHeight);
    return result;
  }

  inline void assign(const T * valuesRowMajor){
    memcpy(_data,valuesRowMajor,dataByteSize());
  }
  inline void getBlock(DynamicMatrix<T> & block, uint i, uint j)const{
    // do eome safety checks here
    if(i+block.rows() > _rows){
      std::cerr << "getBlock error"<<std::endl;
      return;
    }
    if(j+block.cols()>_cols){
      std::cerr << "getBlock error" << std::endl;
      return;
    }
    for(int k=0; k < block.rows();k++){
      T * rowPtr = block.rowData(k);
      memcpy(rowPtr,_data+(i+k)*cols(),block.cols()*sizeof(T));
    }
  }
  template<typename OutputMatrix>
  inline void block(OutputMatrix & r, uint i, uint j)const{
    MatrixExtractBlock<OutputMatrix,DynamicMatrix<T> >::operation(r,*this,i,j,r.rows(),r.cols());
  }
  template<typename OutputMatrix>
  inline void block(OutputMatrix & r, uint i, uint j, uint rows, uint cols)const{
    MatrixExtractBlock<OutputMatrix,DynamicMatrix<T> >::operation(r,*this,i,j,rows,cols);
  }
  inline void setBlock(uint i,uint j, const DynamicMatrix<T> & block){
    // do eome safety checks here
    if(i+block.rows() > _rows){
      std::cerr << "getBlock error"<<std::endl;
      return;
    }
    if(j+block.cols()>_cols){
      std::cerr << "getBlock error" << std::endl;
      return;
    }
    for(int k=0; k < block.rows();k++){
      const T * rowPtr = block.rowData(k);
      memcpy(_data+(i+k)*cols(),rowPtr,block.cols()*sizeof(T));
    }
  }
  inline void assignRows(uint rowCount, const DynamicMatrix<T> & mat ){
    memcpy(_data,mat._data,sizeof(T)*rowCount*_cols);
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
  inline  T maximum()const{
    T t;
    MatrixMaximumElement<T,DynamicMatrix<T> >::operation(t,*this);
    return t;
  }
  inline  T minimum()const{
    T t;
    MatrixMinimumElement<T,DynamicMatrix<T> >::operation(t,*this);
    return t;
  }
  DynamicMatrix():_rows(0),_cols(0),_data(0){resize(0,0);};
  DynamicMatrix(int rows, int cols):_rows(0),_cols(0),_data(0){
    resize(rows,cols);
  }

  inline size_t dataByteSize()const{
    return _rows*_cols*sizeof(T);
  }
  inline DynamicMatrix<T> & operator=(const DynamicMatrix<T> & orig ){
    assign(orig);
    return *this;
  }
  
  inline bool resize(int n, int m, bool setToZero=true){
    if(_rows==n && _cols==m){
      return true; 
    }
    ArrayPool<T>::freeArray(&_data,size());
    _rows = n;
    _cols=m;
    ArrayPool<T>::createArray(&_data,size());

    _rows = n;
    _cols =m;
    if(setToZero) setZero();
    return true;
  }
  inline DynamicMatrix<T> transpose()const {
    DynamicMatrix<T> result;
    MatrixTranspose<DynamicMatrix<T>,DynamicMatrix<T> >::operation(result,*this);
    return result;
  }
  inline Real * rowData(int i){
    return _data +(i*_cols);
  }
  inline const Real * rowData(int i)const{
    return _data+(i*_cols);
  }
  template<typename T2>
  inline void copyTo(T2 * valuePtr){
    for(int i=0; i < size();i++){
      valuePtr[i]=_data[i];
    }
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



  }//endof of matrix2
  //dynamic matrix specialization
 
  


}

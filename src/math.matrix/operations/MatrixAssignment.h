#pragma once
#include <config.h>
#include <math.matrix/operations/MatrixResize.h>
#include <math.matrix/operations/MatrixRowCount.h>
#include <math.matrix/operations/MatrixColumnCount.h>
#include <math.matrix/operations/MatrixElementAssignment.h>
namespace nspace{

  
/**
 * \brief Matrix index type.  has one typedef Type which contains the type used for MatrixType's Indices 
 *        the default is unsigned int
 */
template<typename MatrixType>
class MatrixIndexType{
public:
  typedef unsigned int Type;
};

#define DefineMatrixIndexType(MATRIXTYPE,INDEXTYPE) class MatrixIndexType<MATRIXTYPE>{public: typedef INDEXTYPE Type;};
#define indexTypeOfType(MATRIXTYPE) typename MatrixIndexType<MATRIXTYPE>::Type
#define indexTypeOfInstance(MATRIXINSTANCE) indexTypeOfType(typename decltype(MATRIXINSTANCE))




  /**
   * \brief Matrix coefficient type. template class which has a typedef Type specifing the coefficient type of a MatrixType
   *        The default is double
   */
  template<typename MatrixType>
  class MatrixCoefficientType{
  public:
    typedef double Type;
  };

#define SpecializeMatrixCoefficientType(MATRIXTYPE,COEFFICIENTTYPE) class MatrixCoefficientType<MATRIXTYPE>{public:typedef COEFFICIENTTYPE Type;};
#define coefficientTypeOfType(MATRIXTYPE) typename MatrixCoefficientType<MATRIXTYPE>::Type
#define coefficientTypeOfInstance(MATRIXINSTANCE) typename coefficientTypeOfType( decltype(MATRIXINSTANCE))


  //specialization for scalar types
template<> SpecializeMatrixCoefficientType(double,double);
template<> SpecializeMatrixCoefficientType(float,float);
template<> SpecializeMatrixCoefficientType(int,int);
template<> SpecializeMatrixCoefficientType(unsigned int,unsigned int);
template<> SpecializeMatrixCoefficientType(char,char);
template<> SpecializeMatrixCoefficientType(unsigned char,unsigned char);
// specialization for 2d array
template<typename T, size_t n, size_t m> SpecializeMatrixCoefficientType(T[n][m],T);

template<typename MatrixType>
  class OperationMatrixCoefficientAccess{
  public:
    // the next two lines do not work in vs2010
     //typedef typename indexTypeOfType(MatrixType) Index;
     // typedef typename coefficientTypeOfType(MatrixType) Coefficient;
    static inline coefficientTypeOfType(MatrixType) & operation(MatrixType & matrix,const  indexTypeOfType(MatrixType) & i,const  indexTypeOfType(MatrixType) & j){
      return matrix(i,j);
    }  
    
    static inline const coefficientTypeOfType(MatrixType) & operation(const MatrixType & matrix,const  indexTypeOfType(MatrixType) &i, const indexTypeOfType(MatrixType) & j){
      return matrix(i,j);
    }  
  };

#define SpecializeCoefficientAccess(TYPE,ACCESSCODE)class OperationMatrixCoefficientAccess<TYPE>{\
  public:\
      coefficientTypeOfType(TYPE) & operation(TYPE & matrix, const indexTypeOfType(TYPE) & i,const  indexTypeOfType(TYPE) & j){return ACCESSCODE;}\
      const coefficientTypeOfType(TYPE) & operation(const TYPE & matrix, const indexTypeOfType(TYPE) & i,const indexTypeOfType(TYPE) & j){return ACCESSCODE;}\
  };

  /*  template<> SpecializeCoefficientAccess(double,        matrix);
    template<> SpecializeCoefficientAccess(float,         matrix);
    template<> SpecializeCoefficientAccess(int,           matrix);
    template<> SpecializeCoefficientAccess(unsigned int,  matrix);
    template<> SpecializeCoefficientAccess(char,          matrix);
    template<> SpecializeCoefficientAccess(unsigned char, matrix);*/

    //specialization for const size 2d array
//    template<typename T, size_t n, size_t m> SpecializeCoefficientAccess(T[n][m], matrix[i][j]);
    

  template<typename MatrixType>
  auto coefficient(MatrixType & matrix, const indexTypeOfType(MatrixType) & i,const indexTypeOfType(MatrixType) & j)->coefficientTypeOfType(MatrixType)&{
    return OperationMatrixElementAccess<MatrixType>::operation(matrix,i,j);
  }
  template<typename MatrixType>
  auto coefficient(const MatrixType & matrix, const indexTypeOfType(MatrixType) & i,const indexTypeOfType(MatrixType) & j)->const coefficientTypeOfType(MatrixType)&{
    return OperationMatrixElementAccess<MatrixType>::operation(matrix,i,j);
  }

  


  template<typename MatA, typename MatB>
  class MatrixAssign{
  public:    
    static inline bool operation(MatA &  result, const MatB & val){
      uint rowCount , columnCount;
      if(!OperationRowCount<MatB>::operation(rowCount,val))return false;
      if(!OperationColumnCount<MatB>::operation(columnCount,val))return false;
      
      if(!MatrixResize<MatA>::operation(result,rowCount,columnCount,false))return false;

      for(int i=0; i < rowCount; i++){
        for(int j=0; j < columnCount; j++){
          
          result(i,j)=val(i,j);
        }
      }
      return true;
    }
  };
  template<typename MatB>
  class MatrixAssign<double,MatB>{
  public:
    static inline bool operation(double &  result, const MatB & val){
      if(val.rows()!=1 || val.cols()!=1)return false;
      result=val(0,0);
      return true;
    }
  };
  template<typename MatB>
  class MatrixAssign<float,MatB>{
  public:
    static inline bool operation(float &  result, const MatB & val){
      if(val.rows()!=1 || val.cols()!=1)return false;
      result=val(0,0);
      return true;
    }
  };
  template<>
  class MatrixAssign<double,double>{
  public:
    static inline bool operation(double &  result, const double & value){
      result = value;
      return true;
    }
  };
  template<>
  class MatrixAssign<float,float>{
  public:
    static inline bool operation(float &  result, const float & value){
      result = value;
      return true;
    }
  };
  /*
  template<typename TAssignee, typename TValue>
  class OperationAssignMatrix{
  public:
  static inline bool operation(TAssignee & assignee,const TValue & value){
  assignee = value;
  return true;
  }
  };

  template<typename TValue>
  class OperationAssignMatrix<double,TValue>{
  public:
  static inline bool operation(double & assignee,const TValue & value){
  if(value.rows()>1||value.cols()>1)return false;
  assignee = value(0,0);
  return true;
  }
  };

  template<>
  class OperationAssignMatrix<double,double>{
  public:
  static inline bool operation(double & assignee,const double & value){
  assignee = value;
  return true;
  }
  };

  template<>
  class OperationAssignMatrix<float,float>{
  public:
  static inline bool operation(float & assignee,const float & value){
  assignee = value;
  return true;
  }
  };

  template<typename TValue>
  class OperationAssignMatrix<float,TValue>{
  public:
  static inline bool operation(float & assignee,const TValue & value){
  if(value.rows()>1||value.cols()>1)return false;
  assignee = value(0,0);
  return true;
  }
  };

  */
}

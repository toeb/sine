#pragma once
#include <config.h>

namespace nspace{
  template<typename MatA, typename MatB>
  class MatrixAssign{
  public:
    static inline bool operation(MatA &  result, const MatB & val){
      if(!result.resize(val.rows(), val.cols())){
        std::cout << "MatrixAssign: could not resize result matrix "<<std::endl;
        return false;
      }
      for(int i=0; i < result.rows(); i++){
        for(int j=0; j < result.cols(); j++){
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
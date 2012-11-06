#pragma once

#include <config.h>
namespace nspace{

  template<typename MatrixType> 
  class OperationColumnCount{
  public:
    static inline bool operation(uint & columnCount, const MatrixType & matrix){
      columnCount=matrix.cols();
      return true;
    }
  };

  // specialization
  template<> 
  class OperationColumnCount<double>{
  public:
    static inline bool operation(uint & columnCount, const double & matrix){
      columnCount = 1;
      return true;
    }
  };

  template<> 
  class OperationColumnCount<float>{
  public:
    static inline bool operation(uint & columnCount, const float & matrix){
      columnCount = 1;
      return true;
    }
  };
}
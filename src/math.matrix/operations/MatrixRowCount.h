#pragma once
#include <config.h>
namespace nspace{
  template<typename MatrixType>
  class OperationRowCount{
  public:
    static inline bool operation(uint & rowCount, const MatrixType & matrix){
      rowCount = matrix.rows();
      return true;
    }
  };
  //specialization
  template<>
  class OperationRowCount<double>{
  public:
    static inline bool operation(uint & rowCount, const double & matrix){
      rowCount = 1;
      return true;
    }
  };

  template<>
  class OperationRowCount<float>{
  public:
    static inline bool operation(uint & rowCount, const float & matrix){
      rowCount = 1;
      return true;
    }
  };
}
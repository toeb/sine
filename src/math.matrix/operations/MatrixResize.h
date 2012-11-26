#pragma once
#include <config.h>
#include <math.matrix/operations/MatrixSetConstant.h>
namespace nspace{
  
template<typename TargetType>
class MatrixResize{
public:
static inline bool operation(TargetType  & target, uint rows, uint cols, bool setToZero){
 target.resize(rows,cols);
 if(setToZero) MatrixSetConstant<Real,TargetType>::operation(target,0.0);
 return true;
}
};


template<>
class MatrixResize<double>{
public:
static inline bool operation(double  & target, uint rows, uint cols, bool setToZero){
  if(rows!=1&& cols!=1)return false;
  return true;
}
};
template<>
class MatrixResize<float>{
public:
static inline bool operation(float  & target, uint rows, uint cols, bool setToZero){
  if(rows!=1&& cols!=1)return false;
  return true;
}
};

}

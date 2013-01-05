#pragma once


#include <math.matrix/operations/MatrixBinaryOperation.h>
#include <math.matrix/operations/VectorInnerProduct.h>


#define VectorOperationClass(NAME) class OperationVector##NAME
#define VectorOperationMethod public : static void operation
namespace nspace{

  template<typename LengthType, typename VectorType> void lengthSquared(LengthType & length, const VectorType & vector);
  template<typename LengthType, typename VectorType> void lengthSquared(const VectorType & vector){LengthType length; lengthSquared(length,vector); return length;}
  template<typename VectorType> typename coefficientTypeOfType(VectorType) lengthSquared(const VectorType & vector){return lengthSquared<typename coefficientTypeOfType(VectorType)>(vector);}


  template<typename LengthType, typename VectorType>
  VectorOperationClass(LengthSquared){
    VectorOperationMethod(LengthType & length, const VectorType & vector){
      dot(length,vector);
    }
  };
  
  template<typename LengthType, typename VectorType> void lengthSquared(LengthType & length, const VectorType & vector){
    OperationVectorLengthSquared<LengthType,VectorType>::operation(length,vector);
  }

}


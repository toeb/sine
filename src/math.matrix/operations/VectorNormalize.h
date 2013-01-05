#pragma once
#include <math.matrix/operations/VectorNorm.h>
#include <math.matrix/operations/MatrixElementWiseMultiplication.h>
namespace nspace{

  template<typename VectorType> inline void normalize(VectorType & vector);
  template<typename ResultingType,typename VectorType> inline void normalized(ResultingType & result, const VectorType & vector){assignMatrix(result,vector); normalize(result);}
  template<typename ResultingType,typename VectorType> inline ResultingType normalized(const VectorType & vector){ResultingType result; normalized(result,vector); return result;}
  template<typename VectorType> inline VectorType normalized(const VectorType & vector){ return normalized<VectorType,VectorType>(vector); }
  


  template<typename VectorType>
  VectorOperationClass(Normalize){
    VectorOperationMethod( VectorType & vector){
      auto inverseLength = length(vector);
      multiply(vector,vector,inverseLength);
    }
  };
  
  
  template<typename VectorType> inline void normalize(VectorType & vector);

}
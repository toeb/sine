#pragma once
#include <config.h>


#include <math.matrix/operations/VectorNormSquared.h>

namespace nspace{

  template<typename LengthType, typename VectorType> inline void length(LengthType & l, const VectorType & vector);
  template<typename LengthType, typename VectorType> inline void length(const VectorType & vector){LengthType l; length(l,vector); return l;}
  template<typename VectorType> typename coefficientTypeOfType(VectorType) inline length(const VectorType & vector){return length<typename coefficientTypeOfType(VectorType)>(vector);}


  template<typename LengthType, typename VectorType>
  VectorOperationClass(Length){
    VectorOperationMethod(LengthType & length, const VectorType & vector){
      elementWiseSquareRoot(length, normSquared(vector));
    }
  };
  
  template<typename LengthType, typename VectorType> inline void length(LengthType & l, const VectorType & vector){
    OperationVectorLength<LengthType,VectorType>::operation(l,vector);
  }



template <typename VectorType>
inline void normalize(VectorType & vector){
  auto result = scalar::reciprocal(scalar::squareRoot(dot(vector,vector)));
  multiply(vector, vector, result);

}

template <typename LHS, typename A, typename B, typename C>
inline void normal(LHS & lhs, const A & a,const B & b, const C & c){
  cross(lhs,subtract(b,a),subtract(c,a));
  normalize(lhs);
}
}
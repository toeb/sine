#pragma once
#include <config.h>

#include <math.matrix/operations/MatrixSubtraction.h>
#include <math.matrix/operations/VectorCrossProduct.h>

#include <math.matrix/operations/VectorInnerProduct.h>
#include <math.matrix/operations/MatrixScalarMultiplication.h>
#include <math.scalar/operations.h>
namespace nspace{

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
#pragma once

#include <math.matrix/operations/VectorNormal.h>
#include <math.matrix/operations/MatrixSubtraction.h>

namespace nspace{

  /**
   * \brief calculates the normal of the triangle defined by a,b,c (CCW order)
   *
   * \tparam  typename N  Type of n. (a Vector)
   * \tparam  typename A  Type of a.(a Vector)
   * \tparam  typename B  Type of b.(a Vector)
   * \tparam  typename C  Type of c.(a Vector)
   * \param n The normal.
   * \param a point a of the triangle
   * \param b point b of the triangle
   * \param c point c of the triangle
   */
  template<typename N, typename A, typename B, typename C>  inline void triangleNormal(ARG_OUT(N) n, ARG_IN(A) a, ARG_IN(B) b, ARG_IN(C) c);

  template<typename VectorN, typename VectorA, typename VectorB, typename VectorC>
  inline VectorN triangleNormal(ARG_IN(VectorA) a, ARG_IN(VectorB) b, ARG_IN(VectorC) c){
    VectorN result;
    triangleNormal(result,a,b,c);
    return result;
  }
  template<typename VectorA,typename VectorB, typename VectorC>
  inline typename returnType(VectorA, typename returnType(VectorB,VectorC)) triangleNormal(ARG_IN(VectorA) a, ARG_IN(VectorB) b, ARG_IN(VectorC)c){
    return triangleNormal<typename returnType(VectorA, typename returnType(VectorB,VectorC)),VectorA,VectorB,VectorC>(a,b,c);
  }

  template<typename VectorN, typename VectorA, typename VectorB, typename VectorC>
  class OperationTriangleNormal{
  public:
    static inline void operation(ARG_OUT(VectorN) n, ARG_IN(VectorA) a, ARG_IN(VectorB) b, ARG_IN(VectorC) c){
      normal(n, subtract(b,a), subtract(c,a));
    }
  };
  
  //implementations
  template<typename VectorN, typename VectorA, typename VectorB, typename VectorC>
  inline void triangleNormal(ARG_OUT(VectorN) n, ARG_IN(VectorA) a, ARG_IN(VectorB) b, ARG_IN(VectorC) c){OperationTriangleNormal<VectorN,VectorA,VectorB,VectorC>::operation(n,a,b,c);}

}
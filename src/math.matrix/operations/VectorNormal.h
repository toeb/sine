#pragma once
#include <math.matrix/operations/VectorCrossProduct.h>
#include <math.matrix/operations/VectorNormalize.h>
namespace nspace{

  /**
   * \brief Calculate the Normal of the plane defined by vectors a and b
   *        n = a x b / ||a x b||_2
   *        
   *          
   * \tparam  typename N  Type of Normal.
   * \tparam  typename A  Type of Vector a.
   * \tparam  typename B  Type of Vector b.
   * \param n The resulting normal vector
   * \param a The first input vector
   * \param b The second input vector.
   */
  template<typename N, typename A, typename B> inline void normal(ARG_OUT(N) n, ARG_IN(A) a, ARG_IN(B) b);

  /**
   * \brief Calculate and return the Normal of the plane defined by vectors a and b.
   *
   * \tparam  typename VectorN  Type of vector n.
   * \tparam  typename VectorA  Type of vector a.
   * \tparam  typename VectorB  Type of vector b.
   * \param a vector a
   * \param b vector b
   *
   * \return  n the resulting normal vector.
   */
  template<typename N, typename A, typename B> inline N normal(ARG_IN(A) a, ARG_IN(B) b){
    VectorN result;
    normal(result,a,b);
    return result;
  }

  /**
   * \brief Calculate and return the Normal of the plane defined by vectors a and b.
   *
   * \tparam  typename A  Type of a.
   * \tparam  typename B  Type of b.
   * \param a  vector a.
   * \param b  vector b.
   *
   * \return  the normal vector. (default return type)
   */
  template<typename A, typename B> inline typename returnType(A,B) normal(ARG_IN(A) a, ARG_IN(B) b){
    return normal<typename returnType(A,B),A,A>(a,b);
  }
  
  
  template<typename N, typename A, typename B>
  class OperationNormal{
  public:
    static inline void operation(ARG_OUT(N) normal, ARG_IN(A) a, ARG_IN(B) b){
      cross(normal,a,b);
      normalize(normal);
    }
  };

  //implementation
  template<typename VectorN, typename VectorA, typename VectorB>
  inline void normal(ARG_OUT(VectorN) n, ARG_IN(VectorA) a, ARG_IN(VectorB) b){OperationNormal<VectorN,VectorA,VectorB>::operation(n,a,b);}
  
  
}
#pragma once
#include <common/Config.h>
#include <math/ScalarOperations.h>

namespace nspace{
  template<typename T>
  class VectorOperations{
  public:
  template<typename Vec>
  static inline void crossProduct(Vec & c, const Vec & a, const Vec & b){
    c(0)=a(1)*b(2)-a(2)*b(1);
    c(1)=a(2)*b(0)-a(0)*b(2);
    c(2)=a(0)*b(1)-a(1)*b(0);
  }
  
  template<typename Vec>
  static inline void normSquared(T & nSquared,const Vec & a){
    innerProduct(nSquared,a,a);
  }
  template<typename Vec>
  static void normalize(Vec & v ){
    T l;
    normalize(v,l);
  }
  template<typename Vec>
  static void normalize(Vec & v, T & length){
    norm(length,v);
    if(length < EPSILON){
      v.setZero();
      v(0)=1;
      return;
    }
    MatrixOperations<T>::multiplyScalar(v,v,1.0/length);
   
  }
  template< typename Vec>
   inline static void norm(T & l,const Vec & a){
    normSquared(l,a);
    ScalarOperations<T>::sqrt(l,l);
   }


    template<typename Vec  >
    static inline void maximum(T & result, const Vec & a){
      result = a(0);
      T current;
      for(int i=1; i < a.size(); i++){
        current = a(i);
        if(result < current){
          result = current;
        }
      }
    }
    template<typename Vec>
    static inline void minimum(T & result, Vec & a){
      result = a(0);
      T current;
      for(int i=1; i < a.size(); i++){
        current = a(i);
        if(result > current){
          result = current;
        }
      }
    }




  template<typename Vec>
   static inline void innerProduct(T & result,const Vec & a, const Vec& b){
    result = 0.0;
    int dimension = a.size();
    
    for(int i=0; i < dimension; i++){
      result += a(i)*b(i);
    }
  }
  template<typename VecA, typename VecB, typename Mat>
   static inline void outerProduct( Mat & result,const VecA & a, const VecB & b){
    for(int i=0; i < result.rows(); i++){
      for(int j=0; j < result.cols(); j++){
        result(i,j) = a(i)*b(j);
      }
    }
  }

};




}
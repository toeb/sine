#pragma once
#include <common/Config.h>
#include <math/ScalarOperations.h>

namespace nspace{
  template<typename T>
  class VectorOperations{
  public:
  template<typename Vec>
  inline void crossProduct(Vec & c, const Vec & a, const Vec & b){
    c(0)=a(1)*b(2)-a(2)*b(1);
    c(1)=a(2)*b(0)-a(0)*b(2);
    c(2)=a(0)*b(1)-a(1)*b(0);
  }
  
  template<typename Vec>
  inline void normSquared(T & nSquared,const Vec & a){
    innerProduct(a,a,nSquared);
  }
  template<typename Vec>
  void normalize(Vec & v ){
    T l;
    normalize(v,l);
  }
  template<typename Vec>
  void normalize(Vec & v, T & length){
    norm(length,v);
    divide(v,v,length)
  }
  template< typename Vec>
   inline void norm(T & l,const Vec & a){
    normSquared(l,a);
    ScalarOperations<T>::sqrt(l,l);
   }


    template<typename Vec  >
    inline void maximum(T & result, const Vec & a){
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
    inline void minimum(T & result, Vec & a){
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
   inline void multiply(Vec & c,const Vec & a, const T & s){      
    for(int i=0; i <dimension; i++){
      c(i)=a(i)*s;
    }
  }

  template<typename Vec>
  static inline void divide(Vec & c,const Vec & a, const T & s){
    multiply(a,ScalarOperations<T>::reciprocal(s),c);
  } 

  template<typename Vec>
   inline void innerProduct(T & result,const Vec & a, const Vec& b){
    result = 0.0;
    int dimension = a.size();
    
    for(int i=0; i < dimension; i++){
      result += a(i)*b(i);
    }
  }
  template<typename VecA, typename VecB, typename Mat>
   inline void outerProduct( Mat & result,const VecA & a, const VecB & b){
    for(int i=0; i < result.rows(); i++){
      for(int j=0; j < result.cols(); j++){
        result(i,j) = a(i)*b(j);
      }
    }
  }
  template<typename Vec>
   inline void sum( Vec & result,const Vec & a,const Vec & b){
    for(int i=0; i < result.size(); i++){
      result(i) = a(i)+b(i);
    }
  }
  template<typename Vec>
   inline void elementWiseMultiply( Vec & result,const Vec & a,const Vec & b){

    for(int i=0; i < result.size(); i++){
      result(i) = a(i)*b(i);
    }
  }

  template<typename Vec>
   inline void subtract( Vec & result,const Vec & a,const Vec & b){
    for(int i=0; i < result.size(); i++){
      result(i) = a(i)-b(i);
    }
  }
  template<typename Vec>
   inline void negate( Vec & result,const Vec & a){
    for(int i=0; i < result.size(); i++){
      result(i) = -a(i);
    }
  }
};




}
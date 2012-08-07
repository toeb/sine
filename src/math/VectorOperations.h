#pragma once
#include <common/Config.h>
#include <math/ScalarOperations.h>
#include <math/types/StaticVector.h>
namespace nspace{


  template<typename T, typename Vec>
  inline void normSquared(T & nSquared,const Vec & a){
    innerProduct(a,a,nSquared);
  }
  template<typename Vec>
  void normalize(Vec & v ){
    T l;
    normalize(v,l);
  }
  template<typename T, typename Vec>
  void normalize(Vec & v, T & length){
    norm(length,v);
    divide(v,v,length)
  }
  template<typename T, typename Vec>
   inline void norm(T & l,const Vec & a){
    normSquared(l,a);
    ScalarOperations<T>::sqrt(l,l);
  }
  template<typename T,typename Vec>
   inline void multiply(Vec & c,const Vec & a, const T & s){      
    for(int i=0; i <dimension; i++){
      c(i)=a(i)*s;
    }
  }
  template<typename T,typename Vec>
  static inline void divide(Vec & c,const Vec & a, const T & s){
    multiply(a,ScalarOperations<T>::reciprocal(s),c);
  } 

  template<typename T,typename Vec>
   inline void innerProduct(T & result,const Vec & a, const Vec& b){
    result = 0.0;
    for(int i=0; i < dimension; i++){
      result += a(i)*b(i);
    }
  }
  template<typename T,typename VecA, typename VecB, typename Mat>
   inline void outerProduct( Mat & result,const VecA & a, const VecB & b){
    for(int i=0; i < result.rows(); i++){
      for(int j=0; j < result.cols(); j++){
        result(i,j) = a(i)*b(j);
      }
    }
  }
  template<typename T,typename Vec>
   inline void sum( Vec & result,const Vec & a,const Vec & b){
    for(int i=0; i < result.size(); i++){
      result(i) = a(i)+b(i);
    }
  }
  template<typename T,typename Vec>
   inline void elementWiseMultiply( Vec & result,const Vec & a,const Vec & b){

    for(int i=0; i < result.size(); i++){
      result(i) = a(i)*b(i);
    }
  }
  template<typename T,typename Vec>
   inline void subtract( Vec & result,const Vec & a,const Vec & b){
    for(int i=0; i < result.size(); i++){
      result(i) = a(i)-b(i);
    }
  }
  template<typename T,typename Vec>
   inline void negate( Vec & result,const Vec & a){
    for(int i=0; i < result.size(); i++){
      result(i) = -a(i);
    }
  }
   /*
  template<typename T,typename Vec>
  inline StaticVector<T,dim> operator - (const StaticVector<T,dimension>& v){
    StaticVector<T,dim> result;
    VectorOperations<T>::negate(result,v);
    return result;
  }						
 template<typename T,typename Vec>
  inline StaticVector<T,dim> operator + (const StaticVector<T,dimension>& a, const StaticVector<T,dimension> &b){
    StaticVector<T,dim> result;
    VectorOperations<T>::add(result,a,b);
    return result;
  }				
  template<typename T,typename Vec>
  inline StaticVector<T,dim> operator - (const StaticVector<T,dimension>& a, const StaticVector<T,dimension> &b){
    StaticVector<T,dim> result;
    VectorOperations<T>::subtract(result,a,b);
    return result;
  }		
  template<typename T,typename Vec>
  inline StaticVector<T,dim> operator * (const StaticVector<T,dimension>& a, const T & d){
    StaticVector<T,dim> result;
    VectorOperations<T>::multiply(result,a,d);
    return result;
  }	
  template<typename T,typename Vec>
  inline StaticVector<T,dim> operator * ( const T & d,const StaticVector<T,dimension>& a){
    StaticVector<T,dim> result;
    VectorOperations<T>::multiply(result,a,d);
    return result;
  }	
  template<typename T,typename Vec>
  inline StaticVector<T,dim> operator | ( const StaticVector<T,dimension>& a,const StaticVector<T,dimension>& b){
    StaticVector<T,dim> result;
    VectorOperations<T>::elementWiseMultiply(result,a,b);
    return result;
  }	
 template<typename T,typename Vec>
  inline StaticVector<T,dim> operator * ( const StaticVector<T,dimension>& a,const StaticVector<T,dimension>& b){
    StaticVector<T,dim> result;
    VectorOperations<T>::innerProduct(result,a,b);
    return result;
  }	
  */



}
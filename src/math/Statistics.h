#pragma once
#include <math/definitions.h>

namespace nspace{
  template<typename ScalarType=Real, ScalarType unitElement=1.0, ScalarType zeroElement=0.0>
  class ScalarOperations{
    static inline void add(const ScalarType a, const ScalarType b, ScalarType & sum){
      sum = a+b;
    }
    static inline void subtract(const ScalarType a, const ScalarType b, ScalarType & difference){
      difference = a-b;
    }
    static inline void negative(const ScalarType a, ScalarType & b){
      b = -a;
    }
    static inline void multiply(const ScalarType a, const ScalarType b; ScalarType & c){
      c = a*b;
    }
    static inline void divide(const ScalarType a, const ScalarType b, ScalarType & c){
      c = a / b;
    }
    static inline void sqrt(const ScalarType a, ScalarType & b){
      b = std::sqrt(a);
    }
    static inline void reciprocal(const ScalarType a, ScalarType & b){
      divide(unitElement, a,b);
    }
  };
template<typename ScalarType = Real, typename VectorType = VectorND, typename MatrixType = MatrixNxM>
class VectorOperations{
public:
  static inline void normSquared(const VectorType & a, const ScalarType & l2){
    innerProduct(a,a,l2);
  }
  static inline void norm(const VectorType & a, const ScalarType & l){
    ScalarOperations<ScalarType>::sqrt(normSquared());
  }
  static inline void multiply(const VectorType & a, const ScalarType & s, VectorType & c){
    assert(a.size()==c.size());
    for(int i=0; i < a.size(); i++){
      c(i)=a(i)*s;
    }
  }
  static inline void divide(const VectorType & a, const ScalarType & s, VectorType & c){
    multiply(a,ScalarOperations<ScalarType>::reciprocal(s),c);
  }
  static inline void innerProduct(const VectorType & a, const VectorType & b, ScalarType & result){
    assert(a.size()==b.size());
    result = 0.0
    for(int i=0; i < a.size(); i++){
      result += a(i)*b(i);
    }
  }
  static inline void outerProduct(const VectorType & a, const VectorType & b, MatrixType & result){
    assert(result.rows() == a.size() && result.cols()==b.size());
    for(int i=0; i < a.size(); i++){
      for(int j=0; j < b.size(); j++){
        result(i,j) = a(i)*b(j);
      }
    }
  }
  static inline void sum(const VectorType & a, const VectorType & b, VectorType & result){
    assert(a.size()==b.size() && a.size()== result.size());
    for(int i=0; i < a.size(); i++){
      result(i) = a(i)+b(i);
    }
  }
  static inline void difference(const VectorType & a, const VectorType & b, VectorType & result){
    assert(a.size()==b.size() && a.size()== result.size());
    for(int i=0; i < a.size(); i++){
      result(i) = a(i)-b(i);
    }
  }
  static inline void negative(const VectorType & a, VectorType & b ){
    assert(a.size() == b.size());
    for(int i=0; i < a.size(); i++){
      a(i)=b(i);
    }
  }
  
};

template<typename ScalarType = Real, typename VectorType=VectorND, std::iterator<forward_iterator_tag, VectorType*> SampleIterator = std::vector<VectorType*>::iterator>
class Statistics{
public:
  static inline void mean(SampleIterator begin, SampleIterator end, VectorType & x_mean){
    x_mean.setZero();
    int n=0;
    for(SampleIterator it =begin; i != end; it++){
      VectorOperations<VectorType>::sum(x_mean, **it,x_mean);
      ++n;
    }
    if(n==0)return x_mean;
    VectorOperations<VectorType>::multiply(x_mean, ScalarOperations<ScalarType>::reciprocal((ScalarType)i) );
  }
  static inline void covariance(const VectorType & x, MatrixType & covariance){
    assert(covariance.rows()==x.size() && covariance.cols()==x.size());
    VectorType x_mean;

    VectorOperations::outerProduct(x,x,covariance);
  }
  
  static inline void variance(const VectorType & x, const Vector)
  static inline void covariance(const std::vector<const VectorType*> & samples)

};

}
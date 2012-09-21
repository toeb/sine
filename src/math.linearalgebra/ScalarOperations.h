#pragma once
#include <cmath>  
namespace nspace{

template<typename T>
  class ScalarArcusTangens{
  public:
    static inline void operation(T & c, const T & a){
      c = atan(a);
    }
  };


template<typename T>
class ScalarOperations{
public:
  static inline void Zero(T & element){element =0;}
  static inline void Identity(T& element){element =1;}
  static inline void add(T & sum, const T &a, const T &b){
    sum = a+b;
  }
  static inline void subtract(T & difference, const T & a, const T &b){
    difference = a-b;
  }
  static inline void negate(T & b, const T& a){
    b = -a;
  }
  static inline void multiply(T &c, const T & a, const T & b){
    c = a*b;
  }
  static inline void divide(T & c, const T &a, const T &b ){
    c = a / b;
  }
  static inline void sqrt(T & b, const T& a){
    b = std::sqrt(a);
  }
  static inline void acos(T & b, const T& a){
    b = std::acos(a);
  }
  static inline void sin(T & b, const T& a){
    b = std::sin(a);
  }
  static inline void asin(T & b, const T& a){
    b = std::asin(a);
  }
  static inline void atan2(T & b, const T& a){
    b = std::atan2(a);
  }
  static inline void atan(T & b, const T& a){
    b = std::atan(a);
  }
  static inline void tan(T & b, const T& a){
    b = std::tan(a);
  }
  static inline void cos(T & b, const T& a){
    b = std::cos(a);
  }
  static inline void abs(T & result, const T & a){
    result = std::abs(a);
  }

  static inline void reciprocal( T & b,const T &a){
    divide(b, 1.0,a);
  }
};
}

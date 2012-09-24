#pragma once

#include <config.h>

namespace nspace{

// a templated comparator this template may be specialized for different types
// it is particularly useful for comparing two pointer types which would not be comparable by operator overloading
template<typename A, typename B>
class Comparator{
public:
  static void operation(bool & equal, const A a,const B b){
    equal = a==b;
  }
};

// a shorthand for comparing two types
template<typename A,typename B>
bool compare(A a,B b){
  bool result;
  Comparator<A,B>::operation(result,a,b);
  return result;
}

}
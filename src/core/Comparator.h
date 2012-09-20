#pragma once

#include <config.h>

namespace nspace{

template<typename A, typename B>
class Comparator{
public:
  static void operation(bool & equal, const A a,const B b){
    equal = a==b;
  }
};

template<typename A,typename B>
bool compare(A a,B b){
  bool result;
  Comparator<A,B>::operation(result,a,b);
  return result;
}

}
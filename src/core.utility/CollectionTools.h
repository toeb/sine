#pragma once
#include <config.h>
#include <functional>

namespace nspace{

  template<typename TContainer, typename T>
  bool contains(const TContainer & c, const T & val);
  template<typename TContainer, typename T>
  bool contains(const TContainer & c,const std::function<bool(const T &) > & pred);
}

// implementation

#include <algorithm>
namespace nspace{

  template<typename TContainer, typename T>
  bool contains(const TContainer & c, const T & val){
    return std::find(std::begin(c),std::end(c),val)!= std::end(c);
  }
  template<typename TContainer, typename T>
  bool contains(const TContainer & c,const std::function<bool(const T &) > & pred){
    for(auto i : c){
      if(pred(i))return true;

    }
    return false;
  }
}




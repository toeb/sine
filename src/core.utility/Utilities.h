#pragma once

#include <config.h>
#include <vector>
// stl container utility methods:


namespace nspace{
  template<typename T, typename TContainer>
  bool contains(const TContainer & container){
    return std::find(std::begin(container),std::end(container))!=std::end(container);
  }



  template<typename TContainer>
  TContainer concat(TContainer & container1, TContainer & container2){
    TContainer result;
    result.insert(std::end(result), std::begin(container1), std::end(container1));
    result.insert(std::end(result), std::begin(container2), std::end(container2));
    return result;    
  }

}
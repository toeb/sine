#pragma once

#include <core.h>
namespace nspace{

class FunctionBase{
 public:
 FunctionBase();
};

template<typename TY, typename TX>
class Function : public virtual FunctionBase{
public:
  virtual inline bool evaluate(TY & result, const TX & x){
    return false;
  }
};

}
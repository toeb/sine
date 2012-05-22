#pragma once

#include <Visualization/UserInterface/IValue.h>
#include <functional>
#include <Math/MathDefs.h>

namespace IBDS{
  
class RealValue : public virtual IValue{
private:
  std::function<void (Real v)> setter;
  std::function<Real ()> getter;
public:
  RealValue(const std::string & name, std::function<Real ()> get,std::function<void (Real v)> set);
  void set(const void * val);
  void get(void * val);
};

}
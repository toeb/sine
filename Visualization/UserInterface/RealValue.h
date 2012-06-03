#pragma once

#include <Visualization/UserInterface/IValue.h>
#include <functional>
#include <Math/Vector3D.h>
#include <vector>
namespace IBDS{

class RealValue : public virtual IValue{
private:
  Real * _value;
  std::function<void (Real v)> setter;
  std::function<Real ()> getter;
public:
  RealValue(const std::string & name, Real & value);
  RealValue(const std::string & name, std::function<Real ()> get,std::function<void (Real v)> set);
  void set(const void * val);
  void get(void * val);
};


 
class IntValue : public virtual IValue{
private:
  std::function<void (int v)> setter;
  std::function<int()> getter;
public:
  IntValue(const std::string & name, std::function<int ()> get,std::function<void (int v)> set);
  void set(const void * val);
  void get(void * val);
};

}
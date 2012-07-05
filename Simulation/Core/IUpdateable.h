#pragma once
#include <Simulation/Core/ISimulationObject.h>
#include <Simulation/Core/Time.h>
#include <functional>
namespace IBDS{
class IUpdatable:public virtual ISimulationObject{
public:
  virtual void update(Time t, Time h){};
  virtual void afterStep(Time t, Time h){};
};
class UpdatableDelegate : public IUpdatable{
private:
  std::function<void(Time,Time)> _delegate;
public:
  UpdatableDelegate(std::function<void(Time,Time)> d):_delegate(d){
  
  }
  void update(Time t, Time h){
    _delegate(t,h);
  }
};

}
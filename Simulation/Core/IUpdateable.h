#pragma once
#include <Simulation/Core/ISimulationObject.h>
#include <Math/MathDefs.h>
#include <functional>
namespace IBDS{
class IUpdatable:public virtual  ISimulationObject{
public:
  virtual void update(Real t, Real h){};
  virtual void afterStep(Real t, Real h){};
};
class UpdatableDelegate : public IUpdatable{
private:
  std::function<void(Real,Real)> _delegate;
public:
  UpdatableDelegate(std::function<void(Real,Real)> d):_delegate(d){
  
  }
  void update(Real t, Real h){
    _delegate(t,h);
  }
};
class CommandModule{

};
class ICommand : ISimulationObject{

};
}
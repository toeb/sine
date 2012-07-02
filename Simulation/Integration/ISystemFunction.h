#pragma once

#include <Simulation/Core/ISimulationObject.h>
#include <Simulation/Integration/IIntegrable.h>
namespace IBDS{
class ISystemFunction : public virtual ISimulationObject{
public: 

  virtual void preIntegration(Real t, Real h){};
  virtual void evaluate(Real t, Real h)=0;
  virtual void postIntegration(Real t, Real h){};
  
  virtual IIntegrable & getIntegrable()=0;
};
}
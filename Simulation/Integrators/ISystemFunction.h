#pragma once

#include <Simulation/ISimulationObject.h>
#include <Simulation/Integrators/IIntegrable.h>
namespace IBDS{
class ISystemFunction : public virtual ISimulationObject{
public: 
  virtual void evaluate(Real t, Real h)=0;
  virtual void correct(Real t){};
  virtual IIntegrable & getIntegrable()=0;
};
}
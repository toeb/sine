#pragma once

#include <core/Time.h>

#include <simulation/ISimulationObject.h>
#include <simulation/SimulationModuleBase.h>

#include <simulation.state/IStatefulObject.h>
namespace nspace{
class ISystemFunction : public virtual ISimulationObject{
public: 
  virtual void preIntegration(Time t, Time h){};
  virtual void evaluate(Time t, Time h)=0;
  virtual void postIntegration(Time t, Time h){};  
  virtual void logSystemInfo(std::ostream & ostream)const{};
};
}


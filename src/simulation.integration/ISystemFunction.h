#pragma once

#include <simulation/ISimulationObject.h>
#include <simulation.integration/IStatefulObject.h>
#include <simulation/SimulationModuleBase.h>
#include <common/Time.h>
namespace nspace{
class ISystemFunction : public virtual ISimulationObject{
public: 
  virtual void preIntegration(Time t, Time h){};
  virtual void evaluate(Time t, Time h)=0;
  virtual void postIntegration(Time t, Time h){};  
  virtual void logSystemInfo(std::ostream & ostream)const{};
};
};


#pragma once
#include <simulation/core/ISimulationObject.h>
#include <simulation/time/SimulationTimeProvider.h>
#include <simulation/integration/module/SystemModule.h>
#include <simulation/timing/TimingModule.h>
namespace nspace{


class DefaultSimulationSetup : public ISimulationObject{
  TYPED_OBJECT;
public:  
  SystemModule defaultSystem;
  SimulationTimeProvider simulationTimeProvider;
  TimingModule timings;
  bool initializeObject();
  DefaultSimulationSetup();
};
}
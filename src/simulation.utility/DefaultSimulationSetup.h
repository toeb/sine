#pragma once
#include <simulation/ISimulationObject.h>

#include <simulation.time/SimulationTimeProvider.h>

#include <simulation.timing/TimingModule.h>

#include <simulation.integration/SystemModule.h>
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
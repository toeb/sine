#pragma once
#include <simulation/ISimulationObject.h>

#include <simulation.time/SimulationTimeProvider.h>

#include <simulation.timing/TimingModule.h>

#include <simulation.integration/IntegratingSystem.h>
namespace nspace{
class DefaultSimulationSetup : public ISimulationObject{
  TYPED_OBJECT(DefaultSimulationSetup);
public:  
  IntegratingSystem defaultSystem;
  SimulationTimeProvider simulationTimeProvider;
  TimingModule timings;
  bool initializeObject();
  DefaultSimulationSetup();
};
}
#pragma once
#include <simulation/core/ISimulationObject.h>
#include <simulation/time/SimulationTimeProvider.h>
#include <simulation/integration/module/SystemModule.h>
namespace nspace{


class DefaultSimulationSetup : public ISimulationObject{
public:  
  SystemModule defaultSystem;
  SimulationTimeProvider simulationTimeProvider;
  bool initializeObject();
  DefaultSimulationSetup();
};
}
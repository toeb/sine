#pragma once
#include <Simulation/Dynamics/Connection/Connector.h>
#include <Simulation/Core/SimulationModuleBase.h>
namespace IBDS{
  
class ConnectorModule  :public SimulationModuleBase<Connector>{
public:
  void calculateConnectorPositions(){
    foreach([](Connector * b){b->calculateCachedValues();});
  }
};
}
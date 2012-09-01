#pragma once
#include <simulation/dynamics/connection/Connector.h>
#include <simulation/core/SimulationModuleBase.h>
namespace nspace{
  
class ConnectorModule  :public SimulationModuleBase<DynamicConnector>{
public:
  void calculateConnectorPositions(){
    foreachObject([](DynamicConnector * b){b->calculateCachedValues();});
  }
};
}
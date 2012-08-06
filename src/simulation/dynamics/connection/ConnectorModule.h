#pragma once
#include <simulation/dynamics/connection/Connector.h>
#include <simulation/core/SimulationModuleBase.h>
namespace nspace{
  
class ConnectorModule  :public SimulationModuleBase<Connector>{
public:
  void calculateConnectorPositions(){
    foreachObject([](Connector * b){b->calculateCachedValues();});
  }
};
}
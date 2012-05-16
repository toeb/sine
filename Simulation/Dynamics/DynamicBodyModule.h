#pragma once
#include <Simulation/Dynamics/DynamicBody.h>
#include <Simulation/SimulationModuleBase.h>
namespace IBDS{
 
class DynamicBodyModule : public SimulationModuleBase<DynamicBody>{
public:
  void calculateCachedValues(){
    foreach([](DynamicBody* b){b->calculateCachedValues();});
  }
  void calculateDynamics(){
    foreach([](DynamicBody * b){b->calculateDynamics();});
  }
};
}
#pragma once
#include <Simulation/Dynamics/DynamicBody.h>
#include <Simulation/Core/SimulationModuleBase.h>
#include <Simulation/Core/Timing/Timeable.h>
namespace IBDS{
 
class DynamicBodyModule : public SimulationModuleBase<DynamicBody>, public virtual Timeable{
public:
  DynamicBodyModule(){
    setName("DynamicBodyModule");
  }
  void calculateCachedValues(){
    tick();
    foreach([](DynamicBody* b){b->calculateCachedValues();});
    tock();
  }
  void calculateDynamics(){
    tick();
    foreach([](DynamicBody * b){b->calculateDynamics();});
    tock();
  }
};
}
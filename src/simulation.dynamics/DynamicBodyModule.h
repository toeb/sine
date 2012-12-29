#pragma once
#include <simulation.dynamics/DynamicBody.h>
#include <simulation/SimulationModuleBase.h>
#include <simulation.timing/Timeable.h>
namespace nspace{
  class DynamicBodyModule : public SimulationModuleBase<DynamicBody>, public virtual Timeable{
  public:
    DynamicBodyModule(){
      setName("DynamicBodyModule");
    }
    void calculateCachedValues(){
      tick();//measure time
      foreachObject([](DynamicBody* b){b->calculateCachedValues();});
      tock();
    }
    void calculateDynamics(){
      tick();
      foreachObject([](DynamicBody * b){b->calculateDynamics();});
      tock();
    }
  };
}
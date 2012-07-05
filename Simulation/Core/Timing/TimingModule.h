#pragma once 
#include <Simulation/Core/SimulationModuleBase.h>
#include <Simulation/Core/Timing/Timeable.h>
namespace IBDS{
  class TimingModule : public SimulationModuleBase<Timeable>{
  public:
    void printInfo(std::ostream & out){
      foreach([&out](Timeable * timeable){
        if(!timeable->getName())return;

          out << *timeable->getName() << " time used: " << timeable->accumulatedTime() << " s"<< std::endl ;
      });
      std::cout << std::endl;
    }
    void resetAccumulatedTimes(){
        foreach([](Timeable * timeable){
          timeable->resetAccumulatedTime();
      });
    }
  };
}
#pragma once 
#include <simulation/core/SimulationModuleBase.h>
#include <simulation/timing/Timeable.h>
namespace nspace{
  class TimingModule : public SimulationModuleBase<Timeable>{
  public:
    void printInfo(std::ostream & out){
      foreachObject([&out](Timeable * timeable){
        //if(!timeable->getName())return;

          out << timeable->name() << " time used: " << timeable->accumulatedTime() << " s"<< std::endl ;
      });
      std::cout << std::endl;
    }
    void resetAccumulatedTimes(){
        foreachObject([](Timeable * timeable){
          timeable->resetAccumulatedTime();
      });
    }
  };
}

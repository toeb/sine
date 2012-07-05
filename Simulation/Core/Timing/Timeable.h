#pragma once
#include <Simulation/Core/ISimulationObject.h>
#include <Simulation/Core/Time.h>
namespace IBDS{
  class Timeable : public virtual ISimulationObject{
  private:
    Time _accumulatedTime;
    Time _start;
  public:
    Timeable():_accumulatedTime(0), _start(0){}
    void resetAccumulatedTime(){_accumulatedTime = 0;}
    const Time & accumulatedTime(){
      return _accumulatedTime;
    }
    inline void tick(){
      _start = currentTime();
    }
    inline void tock(){
      _accumulatedTime += _start - currentTime();
    }
    
  };
}
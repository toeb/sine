#pragma once 
#include <Simulation/Core/SimulationModuleBase.h>
#include <Simulation/Core/Timing/Timeable.h>
#include <Simulation/Core/IUpdateable.h>
#include <functional>

namespace IBDS{
  class Timer : public IUpdatable{
  private:
    Time _timeout;
    bool _repeat;
    bool _fire;
    Time _targetTime;
    Time _startTime;

  public:
    Timer(Time timeout=0, bool repeat=true);
    
    virtual void timeout(Time systemTime, Time simulationTime){};

    bool isRunning()const;
    bool & repeat(){return _repeat;}
    void start();
    void stop();
    void restart();

    Time & targetTime(){return _targetTime;}
    Time startTime(){return _startTime;}

    void afterStep(Time t, Time h);
  protected:
    bool initializeObject();
  };

 
  
}
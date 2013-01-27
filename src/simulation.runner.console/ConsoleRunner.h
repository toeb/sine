#pragma once
#include <core/Time.h>
#include <simulation.runner/SimulationRunner.h>
#include <simulation.time/SimulationTimeProvider.h>

namespace nspace{
  class ConsoleRunner : public SimulationRunner{
    TYPED_OBJECT(ConsoleRunner);

    bool running;
    SimulationTimeProvider * simulationTime;
    Time target;
  public:
    ConsoleRunner():running(false),simulationTime(0){
      setName("ConsoleRunner");
    }
    void run(Time secondsToRun){
      target = secondsToRun;
      simulation()->initialize();
      if(simulationTime)simulationTime->advanceTo(REAL_MAX);
      SimulationRunner::run();
    }
    virtual int executeRunner(){
      if(!simulationTime)return 1;
      running = true;

      while(running){
        if(simulationTime->actualTime() >= target){running = false; continue;}
        executeTasks();
      }

      return 0;
    }

    virtual bool initializeRunner(){return true;}

  protected:

    void onPotentialSimulationObjectAdd(ISimulationObject * object){
      auto simTime = dynamic_cast<SimulationTimeProvider*>(object);
      if(simTime){
        simulationTime = simTime;
      }
    }
  };
}

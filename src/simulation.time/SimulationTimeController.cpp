#include "SimulationTimeController.h"
#include <simulation.time/RealTimeProvider.h>
using namespace std;
using namespace nspace;
SimulationTimeController::SimulationTimeController(SimulationTimeProvider & tp, bool startPaused):
  //PeriodicTask(0,RealTimeProvider::defaultInstance()),
  _simulationTimeProvider(tp),
    _Paused(true),
    _DesiredSpeed(1),
    _RealTimeFactor(1),
  _ActualSpeed(1),
  _MeanSpeed(1)
  
{
  
    interval()=0.001;
    isOneTimeTask()=false;
  setPaused(startPaused);
  setName("SimulationTimeController");      
}
   
void SimulationTimeController::togglePause(){
  setPaused(!getPaused());
};

Real SimulationTimeController::actualSpeedAverage(){
  return MeanSpeed().calculate();
}

void SimulationTimeController::timeout(Time dt,Time t){
  if(getPaused())return; 
  _simulationTimeProvider.advanceBy(dt*getDesiredSpeed());
}

#include "SimulationTimeController.h"
#include <simulation.time/RealTimeProvider.h>
using namespace std;
using namespace nspace;

SimulationTimeController::SimulationTimeController(SimulationTimeProvider & tp, bool startPaused):
  //PeriodicTask(0,RealTimeProvider::defaultInstance()),
  _DesiredSpeed(1),
  _Paused(true),
  _MeanSpeed(1),
  _ActualSpeed(1),
  _RealTimeFactor(1),
  _simulationTimeProvider(tp)
{
  setInterval(0.001);
  setIsOneTimeTask(false);
  setPaused(startPaused);
  setName("SimulationTimeController");
}

void SimulationTimeController::togglePause(){
  setPaused(!getPaused());
}

Real SimulationTimeController::actualSpeedAverage(){
  return MeanSpeed().calculate();
}

void SimulationTimeController::timeout(Time dt,Time t){
  if(getPaused())return;
  _simulationTimeProvider.advanceBy(dt*getDesiredSpeed());
}
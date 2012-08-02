#include "SimulationTimeController.h"
#include <simulation/time/RealTimeProvider.h>
using namespace std;
using namespace nspace;
SimulationTimeController::SimulationTimeController(SimulationTimeProvider & tp, bool startPaused):
  PeriodicTask(0,RealTimeProvider::defaultInstance()),
  _simulationTimeProvider(tp),
  _paused(true),
  _desiredSpeed(1),
  _realTimeFactor(1),
  _actualSpeed(1),
  _meanSpeed(1)
{
  setPause(startPaused);
  setName("SimulationTimeController");      
}
   
void SimulationTimeController::setPause(bool flag){
  if(flag == _paused)return;
  _paused = flag; 
};
void SimulationTimeController::togglePause(){
  setPause(!_paused);
};

Real SimulationTimeController::actualSpeedAverage(){
  return _meanSpeed.calculate();
}

void SimulationTimeController::timeout(Time dt){
  if(_paused)return; 
  _simulationTimeProvider.advanceBy(dt*_desiredSpeed);
}

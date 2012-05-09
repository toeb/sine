#include "SimulationRunner.h"
#include <iostream>

using namespace std;
using namespace IBDS;

bool SimulationRunner::initialize(){
  return true;
}
SimulationRunner::SimulationRunner():_simulation(0),_desiredTimeStepSize(0.02),_paused(false){

}
SimulationRunner::~SimulationRunner(){

}
const Real& SimulationRunner::getDesiredTimeStepSize()const{
  return _desiredTimeStepSize;
}
void SimulationRunner::setDesiredTimeStepSize(Real h){
  _desiredTimeStepSize=h;
  onDesiredTimeStepChanged();
}
const char * SimulationRunner::getSimulationName(const Simulation * simulation)const{
  const char * simulationName = simulation->getName();
  if(!simulationName){
    simulationName ="Unnamed Simulation";
  }
  return simulationName;

}
void SimulationRunner::doTimestep(Real dt){
  
  if(!_simulation){
   cerr<<"SimulationRunner: No Simulation set"<<endl;
   return;
  }
  if(!_simulation->isSimulationValid()){
    cerr<<"SimulationRunner: Simulation is Invalid"<<endl;
    return;
  }
  if(isPaused())return;
  Real targetTime = _simulation->getTime();
  targetTime+= dt;
  _simulation->simulate(targetTime);
}
void SimulationRunner::cleanup(){
  if(!_simulation)return;
  _simulation->cleanup();
}

Simulation * SimulationRunner::getSimulation(){
  return _simulation;
}

void SimulationRunner::setSimulation(Simulation * simulation){
  _simulation = simulation;
  onSimulationSet();
}
bool SimulationRunner::isPaused()const{
  return _paused;
}
void SimulationRunner::setPaused(bool pause){
  _paused = pause;
  onPausedChanged();
}
void SimulationRunner::togglePause(){
  setPaused(!isPaused());
}

void SimulationRunner::resetSimulation(){
  if(!getSimulation())return;
  getSimulation()->reset();
}


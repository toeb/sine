#include "SimulationRunner.h"
#include <iostream>

using namespace std;
using namespace IBDS;
SimulationRunner::SimulationRunner():_simulation(0),_desiredTimeStepSize(0){

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

void SimulationRunner::doTimestep(Real dt){
  if(!_simulation){
   cerr<<"SimulationRunner: No Simulation set"<<endl;
   return;
  }
  if(!_simulation->isSimulationValid()){
    cerr<<"SimulationRunner: Simulation is Invalid"<<endl;
    return;
  }
  
  Real targetTime = _simulation->getTime();
  targetTime+= dt;
  _simulation->simulate(targetTime);
}
void SimulationRunner::cleanup(){
  if(!_simulation)return;
  _simulation->cleanup();
}
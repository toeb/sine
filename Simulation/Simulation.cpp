#include "Simulation.h"

using namespace IBDS;
using namespace std;


Simulation::Simulation():
  _time(0),
  _targetTime(0)
{
}

void Simulation::reset(){
  for(auto it = _simulationAlgorithms.begin(); it != _simulationAlgorithms.end(); it++){
    (*it)->reset();
  }
  buildModel();
}

Simulation::~Simulation(){}

bool Simulation::addSimulationAlgorithm(ISimulationAlgorithm * algorithm){
  for(auto it = _simulationAlgorithms.begin(); it != _simulationAlgorithms.end(); it++){
    if(!(*it)->isCompatibleWith(algorithm))return false;
  }
  _simulationAlgorithms.push_back(algorithm);
  // add all existing sim objects to new algorithm
  for(auto it = _simulationObjects.begin(); it!=_simulationObjects.end(); it++){
    algorithm->addSimulationObject(*it);
  }
  // since an algorithm is also a simulation object it is added as well.
  addSimulationObject(algorithm);
  return true;
}

bool Simulation::addSimulationObject(ISimulationObject * object){
  bool objectWasAdded = false;
  
  _simulationObjects.push_back(object);
  //tries to add the new object to every algorithm.
  for(auto it = _simulationAlgorithms.begin(); it != _simulationAlgorithms.end(); it++){
    if( (*it)->addSimulationObject(object)){
      objectWasAdded=true;
    }
  }  
  onSimulationObjectAdded(object);
  return objectWasAdded;
}


const Real & Simulation::getTargetTime(){return _targetTime;}
const Real & Simulation::getTime(){return _time;}


void Simulation::simulate(Real targetTime){
  // simulation is only allow forwards so this method fails quietly when targetTime < time
  if(targetTime < _time)return;
  _targetTime = targetTime;
  Real h = _targetTime - _time;

  
  for(auto it = _simulationAlgorithms.begin(); it!=_simulationAlgorithms.end(); it++){
    (*it)->precomputeStep();
  }

  for(auto it = _simulationAlgorithms.begin(); it!=_simulationAlgorithms.end(); it++){
    (*it)->preIntegrationStep(_time,h);
  }
  
  for(auto it = _simulationAlgorithms.begin(); it!=_simulationAlgorithms.end(); it++){
    (*it)->integrationStep(_time,h);
  }  
  _time = targetTime;
  
  for(auto it = _simulationAlgorithms.begin(); it!=_simulationAlgorithms.end(); it++){
    (*it)->postIntegrationStep(_time,h);
  }

  
}



bool Simulation::initialize(){
  buildAlgorithms();
  buildModel();
  bool success=true;
  for(auto it = _simulationObjects.begin(); it != _simulationObjects.end(); it++){
    if(!(*it)->initialize())success = false;
  }
  return success;
}

#include "ForceAlgorithm.h"

using namespace IBDS;

ForceAlgorithm::ForceAlgorithm(){
  setName("Forces Algorithm");
}

bool ForceAlgorithm::addSimulationObject(ISimulationObject *object){
  Force * force  = dynamic_cast<Force*>(object);
  bool added = false;
  if(force){
    _forces.push_back(force);
    added = true;
  }
  DynamicBody * body = dynamic_cast<DynamicBody*>(object);
  if(body){
    _forceAccumulators.push_back(body);
    added = true;
  }
  return added;
}
bool ForceAlgorithm::removeSimulationObject(ISimulationObject * object){
  return false;
}

void ForceAlgorithm::resetForces(){  
  for(auto it = _forceAccumulators.begin(); it != _forceAccumulators.end(); it++){
    (*it)->resetForce();
  }  
}
void ForceAlgorithm::setForces(Real time){
  resetForces();
  applyForces(time);
}
void ForceAlgorithm::applyForces(Real time){
   for(auto it = _forces.begin(); it != _forces.end(); it++){
     (*it)->act(_forceAccumulators,time);
  }  
}

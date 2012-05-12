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
  Body * body = dynamic_cast<Body*>(object);
  if(body){
    _forceAccumulators.push_back(body);
    added = true;
  }
  return added;
}

void ForceAlgorithm::precomputeStep(){  
  for(auto it = _forceAccumulators.begin(); it != _forceAccumulators.end(); it++){
    (*it)->resetForce();
  }  
}
void ForceAlgorithm::preIntegrationStep(Real time, Real h){
   for(auto it = _forces.begin(); it != _forces.end(); it++){
     (*it)->act(_forceAccumulators,time);
  }  
}
void ForceAlgorithm::reset(){
  _forceAccumulators.clear();
  _forces.clear();
}
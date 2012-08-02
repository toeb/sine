#include "ForceAlgorithm.h"

#include <algorithm>

using namespace std;
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
  /*
  for(auto it = _forceAccumulators.begin(); it != _forceAccumulators.end(); it++){
    (*it)->resetForce();
  }  */
  for_each(_forceAccumulators.begin(),_forceAccumulators.end(),[](DynamicBody * b){b->resetForce();});
}
void ForceAlgorithm::setForces(Real time){
  tick();

  resetForces();
  applyForces(time);
  
  tock();
}
void ForceAlgorithm::applyForces(Real time){
  tick();

  for_each(_forces.begin(),_forces.end(),
    [&time, this](Force * force){
      force->act(_forceAccumulators,time);
  });
 
  tock();
}

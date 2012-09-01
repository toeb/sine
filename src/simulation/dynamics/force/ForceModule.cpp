#include "ForceModule.h"

#include <algorithm>

using namespace std;
using namespace nspace;

ForceAlgorithm::ForceAlgorithm(){
  setName("Forces Algorithm");
}

void ForceAlgorithm::announce(ISimulationObject *object){
  Force * force  = dynamic_cast<Force*>(object);

  if(force){
    _forces.push_back(force);

  }
  DynamicBody * body = dynamic_cast<DynamicBody*>(object);
  if(body){
    _forceAccumulators.push_back(body);

  }

}
void ForceAlgorithm::renounce(ISimulationObject * object){
 
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

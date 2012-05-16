#include "ImpulseBasedDynamicsAlgorithm.h"
#include <algorithm>

using namespace std;
using namespace IBDS;

ImpulseBasedDynamicsAlgorithm::ImpulseBasedDynamicsAlgorithm(int maxIterations, Real normalisation, Real positionTolerance, Real velocityTolerance){
  setName("Impulse Based Dynamics Algorith");
  _eps_p=positionTolerance;
  _eps_v=velocityTolerance;
  _maxIterations=maxIterations;
  _normalisation=normalisation;
}

bool ImpulseBasedDynamicsAlgorithm::addSimulationObject(ISimulationObject* object){
  Joint* joint = dynamic_cast<Joint*>(object);
  if(!joint) return false;
  _joints.push_back(joint);
  return true;
}
bool ImpulseBasedDynamicsAlgorithm::removeSimulationObject(ISimulationObject * object){
  auto pos = find(_joints.begin(), _joints.end(),object);
  if(pos == _joints.end())return false;
  _joints.erase(pos);
  return true;
}

void ImpulseBasedDynamicsAlgorithm::correctPositions(Real h){
   bool toleranceSatisfied;  
  _iterations  = 0;
  // do steps before correction
  for (auto it = _joints.begin(); it != _joints.end(); it++) {
    Joint* joint = *it;
    joint->precompute();
  }

  do {
    toleranceSatisfied = true;
    for (auto it = _joints.begin(); it != _joints.end(); it++) {
      Joint* joint = *it;
      joint->correctPosition(h);
      // if correctPosition returns false for some joint, toleranceSatisfied remains false for the rest of the loop 
      if(!joint->arePositionsCorrect())toleranceSatisfied=false;
    }
    _iterations++;
  } while (!toleranceSatisfied && _iterations < _maxIterations);	// the loop is repeated until correctPosition returns true for all joints

}
void ImpulseBasedDynamicsAlgorithm::correctVelocities(){
  for (vector<Joint*>::iterator it = _joints.begin(); it != _joints.end(); it++){
    (*it)->correctVelocity();
  }
}

int ImpulseBasedDynamicsAlgorithm::getLastNumberOfIterations()const{
  return _iterations;
}

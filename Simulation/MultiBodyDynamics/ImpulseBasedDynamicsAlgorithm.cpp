#include "ImpulseBasedDynamicsAlgorithm.h"
#include <algorithm>

using namespace std;
using namespace IBDS;

ImpulseBasedDynamicsAlgorithm::ImpulseBasedDynamicsAlgorithm(int maxIterations, Real normalisation, Real positionTolerance, Real velocityTolerance){
  setName("Impulse Based Dynamics Algorithm");
  _eps_p=positionTolerance;
  _eps_v=velocityTolerance;
  _maxIterations=maxIterations;
  _normalisation=normalisation;
}

void ImpulseBasedDynamicsAlgorithm::correctPositions(Real h){
   bool toleranceSatisfied;  
  _iterations  = 0;
  // do steps before correction
  foreachJoint([](Joint* joint){
    joint->precompute();
  });
  //run position correction loop
  do {
    toleranceSatisfied = true;
    foreachJoint([&toleranceSatisfied, &h](Joint* joint){
      joint->correctPosition(h);
      // if correctPosition returns false for some joint, toleranceSatisfied remains false for the rest of the loop 
      if(!joint->arePositionsCorrect())toleranceSatisfied=false;
    });
    _iterations++;
  } while (!toleranceSatisfied && _iterations < _maxIterations);	// the loop is repeated until correctPosition returns true for all joints

}
void ImpulseBasedDynamicsAlgorithm::correctVelocities(){
  foreachJoint([](Joint* joint){
    joint->correctVelocity();
  });
}

int ImpulseBasedDynamicsAlgorithm::getLastNumberOfIterations()const{
  return _iterations;
}

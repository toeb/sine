#pragma once
#include <Simulation/MultiBodyDynamics/Joint.h>
#include <Simulation/Core/SimulationModuleBase.h>
#include <vector>
namespace IBDS{
  
class ImpulseBasedDynamicsAlgorithm : public SimulationModuleBase<Joint>{
private:
  Real _normalisation;
  ///< The position tolerance
  Real _eps_p;
  ///< The the velocity tolerance
  Real _eps_v;
  ///< The maximum number of iterations
  int _maxIterations;
  ///< The iterations used in last step
  int _iterations;
  std::vector<Joint *> _temporaryJoints;
public:
  int getLastNumberOfIterations()const;
  ImpulseBasedDynamicsAlgorithm(int maxIterations=10, Real normalisation=100, Real positionTolerance=10e-3, Real velocityTolerance=10e-4);
  
  void foreachJoint(std::function<void(Joint *)> f){
    foreach(f);
    for_each(_temporaryJoints.begin(), _temporaryJoints.end(),f);
  }
  void clearTemporaryJoints(){
    _temporaryJoints.clear();
  }
  void addTemporaryJoint(Joint & j){
    _temporaryJoints.push_back(&j);
  }

  void correctPositions(Real h);
  void correctVelocities();
  

};

}
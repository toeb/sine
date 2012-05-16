#pragma once
#include <Simulation/MultiBodyDynamics/Joint.h>
#include <Simulation/ISimulationModule.h>
#include <vector>
namespace IBDS{
  
class ImpulseBasedDynamicsAlgorithm : public ISimulationModule{
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
  ///< The joints this algorithm uses
  std::vector<Joint *> _joints;
public:
  int getLastNumberOfIterations()const;
  ImpulseBasedDynamicsAlgorithm(int maxIterations=10, Real normalisation=100, Real positionTolerance=10e-3, Real velocityTolerance=10e-4);
  
  void correctPositions(Real h);
  void correctVelocities();
  
  bool addSimulationObject(ISimulationObject* object);
  bool removeSimulationObject(ISimulationObject * object);

};

}
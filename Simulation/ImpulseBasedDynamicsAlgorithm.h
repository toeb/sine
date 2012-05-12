#pragma once
#include <Simulation/SimulationObjects/Joint.h>
#include <Simulation/ISimulationAlgorithm.h>
#include <vector>
namespace IBDS{
  
class ImpulseBasedDynamicsAlgorithm : public ISimulationAlgorithm{
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
  void reset();
  bool addSimulationObject(ISimulationObject* object);
  void preIntegrationStep(Real time, Real h);
  void postIntegrationStep(Real time, Real h);
};

}
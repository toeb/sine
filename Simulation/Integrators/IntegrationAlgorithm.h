#pragma once
#include <Simulation/ISimulationAlgorithm.h>
#include <Simulation/Integrators/Integrator.h>
#include <Simulation/Integrators/CompositeIntegratable.h>
namespace IBDS{

/**
 * \brief Integration algorithm. Wraps Integrator into ISimulation Algorithm
 *
 * \author Tobi
 * \date 12.05.2012
 */
class IntegrationAlgorithm : public ISimulationAlgorithm{
private:
  Integrator & _integrator;
  CompositeIntegratable _integrables;
public:
  IntegrationAlgorithm(Integrator & integrator);
  bool isCompatibleWith(ISimulationAlgorithm * algorithm);
  bool addSimulationObject(ISimulationObject * object);
  void reset();
  void integrationStep(Real time, Real h);
};


}
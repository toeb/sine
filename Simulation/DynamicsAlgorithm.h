#pragma once
#include <Simulation/MultiBodyDynamics/ImpulseBasedDynamicsAlgorithm.h>
#include <Simulation/Force/ForceAlgorithm.h>
#include <Simulation/Dynamics/DynamicBodyModule.h>
#include <Simulation/Dynamics/ConnectorModule.h>
#include <Simulation/Integrators/CompositeIntegratable.h>
#include <Simulation/Integrators/ISystemFunction.h>
#include <Simulation/CompositeSimulationModule.h>

namespace IBDS{
  class DynamicsAlgorithm  :  
  public virtual ISystemFunction, 
  public virtual CompositeSimulationModule
{
public:
  ImpulseBasedDynamicsAlgorithm multiBodyDynamics;
  ForceAlgorithm forceModule;
  DynamicBodyModule dynamicBodyModule;
  CompositeIntegratable integrables;
  ConnectorModule connectorModule;
  DynamicsAlgorithm();

  IIntegrable & getIntegrable();

  void evaluate(Real t, Real h);
  void postIntegration(Real t, Real h);
  void preIntegration(Real t, Real h);
};
}
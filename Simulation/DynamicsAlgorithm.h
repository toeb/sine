#pragma once
#include <Simulation/MultiBodyDynamics/ImpulseBasedDynamicsAlgorithm.h>
#include <Simulation/Force/ForceAlgorithm.h>
#include <Simulation/Dynamics/DynamicBodyModule.h>
#include <Simulation/Dynamics/ConnectorModule.h>
#include <Simulation/Integrators/CompositeIntegratable.h>
#include <Simulation/Integrators/ISystemFunction.h>
#include <Simulation/Core/CompositeSimulationModule.h>
#include <Simulation/Textiles/TextileAlgorithm.h>

namespace IBDS{

  /**
   * \brief Dynamics algorithm. 
   * 				Represents the algorithm setup for the simulation
   * 				
   * 				it currently combines
   * 				* ImpulseBasedDynamicsAlgorithm  
   * 				* Force (Spring)  
   * 				* Connectors  
   * 				* Rigid Body Dynamics
   *
   * \author Tobi
   * \date 20.05.2012
   */
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
  TextileAlgorithm textilesModule;
  DynamicsAlgorithm();

  IIntegrable & getIntegrable();

  void evaluate(Real t, Real h);
  void postIntegration(Real t, Real h);
  void preIntegration(Real t, Real h);
};
}
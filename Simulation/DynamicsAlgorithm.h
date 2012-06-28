#pragma once
#include <Simulation/MultiBodyDynamics/ImpulseBasedDynamicsAlgorithm.h>
#include <Simulation/Force/ForceAlgorithm.h>
#include <Simulation/Dynamics/DynamicBodyModule.h>
#include <Simulation/Dynamics/ConnectorModule.h>
#include <Simulation/Integration/CompositeIntegratable.h>
#include <Simulation/Integration/ISystemFunction.h>
#include <Simulation/Core/CompositeSimulationModule.h>
#include <Simulation/Textiles/TextileAlgorithm.h>
#include <Simulation/Core/UpdateablesModule.h>
#include <Simulation/Collision/Detection/CompositeCollisionDetector.h>
#include <Simulation/Collision/Handling/ContactHandler.h>

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
  UpdatablesModule updatablesModule;
  CompositeCollisionDetector collisionDetector;
  ContactHandler contactHandler;

  DynamicsAlgorithm();

  IIntegrable & getIntegrable();

  bool detectCollisions;
  bool handleCollisions;
  bool doMultiBody;
  
  void evaluate(Real t, Real h);
  void postIntegration(Real t, Real h);
  void preIntegration(Real t, Real h);
  
};
}
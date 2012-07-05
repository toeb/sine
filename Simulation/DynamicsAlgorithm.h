#pragma once
#include <Simulation/MultiBodyDynamics/ImpulseBasedDynamicsAlgorithm.h>
#include <Simulation/Collision/Handling/ImpulseBased/ImpulseBasedCollisionHandler.h>
#include <Simulation/Force/ForceAlgorithm.h>
#include <Simulation/Dynamics/DynamicBodyModule.h>
#include <Simulation/Dynamics/Connection/ConnectorModule.h>
#include <Simulation/Integration/CompositeIntegratable.h>
#include <Simulation/Integration/ISystemFunction.h>
#include <Simulation/Core/CompositeSimulationModule.h>
#include <Simulation/Textiles/TextileAlgorithm.h>
#include <Simulation/Core/UpdateablesModule.h>
#include <Simulation/Collision/Detection/CompositeCollisionDetector.h>
#include <Simulation/Core/Timing/TimingModule.h>
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
   * 				* 
   */
  class DynamicsAlgorithm  :  
  public virtual ISystemFunction, 
  public virtual CompositeSimulationObject
{
public:
  ImpulseBasedMultiBodyModule multiBodyDynamics;
  ForceAlgorithm forceModule;
  DynamicBodyModule dynamicBodyModule;
  CompositeIntegratable integrables;
  ConnectorModule connectorModule;
  TextileModule textilesModule;
  UpdatablesModule updatablesModule;
  CompositeCollisionDetector collisionDetector;
  ImpulseBasedCollisionHandler collisionHandler;
  TimingModule timingModule;
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
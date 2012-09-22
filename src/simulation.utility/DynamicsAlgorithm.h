#pragma once
#include <simulation.dynamics.multibody.impulsebased/ImpulseBasedMultiBodyModule.h>
//#include <simulation/Collision/Handling/ImpulseBased/ImpulseBasedCollisionHandler.h>
#include <simulation.dynamics.force/ForceModule.h>
#include <simulation.dynamics/DynamicBodyModule.h>
#include <simulation.dynamics/connection/ConnectorModule.h>
#include <simulation.state/CompositeStatefulObject.h>
#include <simulation.integration/ISystemFunction.h>
#include <simulation/composites/CompositeSimulationObject.h>
//#include <simulation/Textiles/TextileAlgorithm.h>
//#include <simulation/Core/UpdateablesModule.h>
//#include <simulation/Collision/Detection/CompositeCollisionDetector.h>

#include <simulation.timing/TimingModule.h>
namespace nspace{



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
  ConnectorModule connectorModule;
  //TextileModule textilesModule;
  //UpdatablesModule updatablesModule;
  //CompositeCollisionDetector collisionDetector;
  //ImpulseBasedCollisionHandler collisionHandler;
  TimingModule timingModule;
  DynamicsAlgorithm();


  bool detectCollisions;
  bool handleCollisions;
  bool doMultiBody;
  
  void evaluate(Real t, Real h);
  void postIntegration(Real t, Real h);
  void preIntegration(Real t, Real h);

};
}

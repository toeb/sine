#include "DynamicsAlgorithm.h"

using namespace std;
using namespace IBDS;


DynamicsAlgorithm::DynamicsAlgorithm(){
  addSimulationModule(&forceModule);
  addSimulationModule(&multiBodyDynamics);
  addSimulationModule(&dynamicBodyModule);
  addSimulationModule(&integrables);
  addSimulationModule(&connectorModule);
  addSimulationModule(&textilesModule);
}

IIntegrable & DynamicsAlgorithm::getIntegrable(){
  return integrables;
}

void DynamicsAlgorithm::evaluate(Real t, Real h){
  //this does not have to be done every time.  

  /*/ calculates the inverted inertia tensor in world coordinates at time t
  // also calculates the rotation and inverted rotation matrices
  dynamicBodyModule.calculateCachedValues(); 
  //precomputes the connector positions
  connectorModule.calculateConnectorPositions();
  // sets the forces for each body
  forceModule.setForces(t);*/  
  //calculates the accelerations of the dynamic bodies (evaluates the mass equations)
  
    
  //multiBodyDynamics.correctPositions(h);
}
void DynamicsAlgorithm::preIntegration(Real t, Real h){
  // calculates the inverted inertia tensor in world coordinates at time t
  // also calculates the rotation and inverted rotation matrices
  dynamicBodyModule.calculateCachedValues(); 
  //precomputes the connector positions
  connectorModule.calculateConnectorPositions();
  // sets the forces for each body
  forceModule.setForces(t);
 dynamicBodyModule.calculateDynamics();
  multiBodyDynamics.correctPositions(h);
}
void DynamicsAlgorithm::postIntegration(Real t,Real h){
  multiBodyDynamics.correctVelocities();
  textilesModule.normalize();
}

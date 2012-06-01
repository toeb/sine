#include "DynamicsAlgorithm.h"

using namespace std;
using namespace IBDS;


DynamicsAlgorithm::DynamicsAlgorithm():multiBodyDynamics(20){
  addSimulationModule(&forceModule);
  addSimulationModule(&multiBodyDynamics);
  addSimulationModule(&updatablesModule);
  addSimulationModule(&dynamicBodyModule);
  addSimulationModule(&integrables);
  addSimulationModule(&connectorModule);
  addSimulationModule(&textilesModule);
  addSimulationModule(&octreeCollisionDetector);
}

IIntegrable & DynamicsAlgorithm::getIntegrable(){
  return integrables;
}

void DynamicsAlgorithm::evaluate(Real t, Real h){
  dynamicBodyModule.calculateCachedValues(); 
  connectorModule.calculateConnectorPositions();
  forceModule.setForces(t);
  dynamicBodyModule.calculateDynamics();
}
void DynamicsAlgorithm::preIntegration(Real t, Real h){
  
  dynamicBodyModule.calculateCachedValues(); 
  connectorModule.calculateConnectorPositions();
  
  updatablesModule.update(t,h);  

  if(detectCollisions){
    octreeCollisionDetector.reset();
    octreeCollisionDetector.update();
    octreeCollisionDetector.detectCollisions(t,h);
    cout << "Collisions Detected: "<<octreeCollisionDetector.getCollisionCount()<<endl;
    cout << "Contacts: "<<octreeCollisionDetector.getContactCount()<<endl;

  }
  if(doMultiBody)multiBodyDynamics.correctPositions(h);
  
}
void DynamicsAlgorithm::postIntegration(Real t,Real h){
  if(doMultiBody)multiBodyDynamics.correctVelocities();
  textilesModule.normalize();
}

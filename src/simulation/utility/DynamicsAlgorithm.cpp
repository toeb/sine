#include "DynamicsAlgorithm.h"



using namespace std;
using namespace IBDS;


DynamicsAlgorithm::DynamicsAlgorithm():multiBodyDynamics(20),doMultiBody(true),detectCollisions(true),collisionHandler(collisionDetector,multiBodyDynamics){
  addChild(&forceModule);
  addChild(&multiBodyDynamics);
  addChild(&updatablesModule);
  addChild(&dynamicBodyModule);
  addChild(&integrables);
  addChild(&connectorModule);
  addChild(&textilesModule);
  addChild(&collisionDetector);
  addChild(&collisionHandler);
  addChild(&timingModule);
}

IIntegrable & DynamicsAlgorithm::getIntegrable(){
  return integrables;
}


void DynamicsAlgorithm::preIntegration(Real t, Real h){
  dynamicBodyModule.calculateCachedValues(); 
  connectorModule.calculateConnectorPositions();
  updatablesModule.update(t,h);
  collisionHandler.reset();
  if(detectCollisions){
    collisionDetector.reset();
    collisionDetector.update();
    collisionDetector.detectCollisions(t,h);
  collisionHandler.handleCollisions();
  }
  if(doMultiBody)multiBodyDynamics.correctPositions(h);
}

void DynamicsAlgorithm::evaluate(Real t, Real h){
  dynamicBodyModule.calculateCachedValues(); 
  connectorModule.calculateConnectorPositions();
  forceModule.setForces(t);
  dynamicBodyModule.calculateDynamics(); 
}

void DynamicsAlgorithm::postIntegration(Real t,Real h){
  if(doMultiBody)multiBodyDynamics.correctVelocities();
  textilesModule.normalize();

  updatablesModule.afterStep(t,h);
}





#include "DynamicsAlgorithm.h"



using namespace std;
using namespace nspace;


DynamicsAlgorithm::DynamicsAlgorithm()//:
// multiBodyDynamics(20),
//   doMultiBody(true),
//   detectCollisions(true),
//   collisionHandler(collisionDetector,multiBodyDynamics)
{
  addComponent(&forceModule);
//   addComponent(&multiBodyDynamics);
//   addComponent(&updatablesModule);
  addComponent(&dynamicBodyModule);
  addComponent(&connectorModule);
//   addComponent(&textilesModule);
//   addComponent(&collisionDetector);
//   addComponent(&collisionHandler);
  addComponent(&timingModule);
}


void DynamicsAlgorithm::preIntegration(Real t, Real h){
//   dynamicBodyModule.calculateCachedValues(); 
//   connectorModule.calculateConnectorPositions();
//   updatablesModule.update(t,h);
//   collisionHandler.reset();
//   if(detectCollisions){
//     collisionDetector.reset();
//     collisionDetector.update();
//     collisionDetector.detectCollisions(t,h);
//   collisionHandler.handleCollisions();
//   }
//   if(doMultiBody)multiBodyDynamics.correctPositions(h);
}

void DynamicsAlgorithm::evaluate(Real t, Real h){
  dynamicBodyModule.calculateCachedValues(); 
  connectorModule.calculateConnectorPositions();
  forceModule.setForces(t);
  dynamicBodyModule.calculateDynamics(); 
}

void DynamicsAlgorithm::postIntegration(Real t,Real h){
//   if(doMultiBody)multiBodyDynamics.correctVelocities();
//   textilesModule.normalize();
// 
//   updatablesModule.afterStep(t,h);
}





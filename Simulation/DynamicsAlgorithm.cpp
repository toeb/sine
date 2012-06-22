#include "DynamicsAlgorithm.h"

using namespace std;
using namespace IBDS;


DynamicsAlgorithm::DynamicsAlgorithm():multiBodyDynamics(20),doMultiBody(true),detectCollisions(true){
  addSimulationModule(&forceModule);
  addSimulationModule(&multiBodyDynamics);
  addSimulationModule(&updatablesModule);
  addSimulationModule(&dynamicBodyModule);
  addSimulationModule(&integrables);
  addSimulationModule(&connectorModule);
  addSimulationModule(&textilesModule);
  addSimulationModule(&collisionDetector);
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
    collisionDetector.reset();
    collisionDetector.update();
    collisionDetector.detectCollisions(t,h);
    //cout << "Collisions Detected: "<<collisionDetector.getCollisionCount()<<endl;
    //cout << "Contacts: "<<collisionDetector.getContactCount()<<endl;

	//collisionDetector.foreachCollision([](Collision *collision) {
	//	collision->foreachContact([collision](Contact *contact) {
	//		ContactType type;
	//		if ((type = collision->classifyContact(*contact)) != UNKNOWN) {
	//			cout << type;
	//			}
	//		});
	//	});

  }
  if(doMultiBody)multiBodyDynamics.correctPositions(h);
  
}
void DynamicsAlgorithm::postIntegration(Real t,Real h){
  if(doMultiBody)multiBodyDynamics.correctVelocities();
  textilesModule.normalize();
}

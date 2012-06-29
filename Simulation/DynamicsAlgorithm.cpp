#include "DynamicsAlgorithm.h"
#include "Dynamics\RigidBodyConnector.h"
#include "Visualization\MiniGL.h"
#include "Simulation\MultiBodyDynamics\ImpulseBasedDynamicsAlgorithm.h"

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
	addSimulationModule(&contactHandler);
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

		//cout << "Collisions Detected: "<<collisionDetector.getCollisionCount()<<endl;
		//cout << "Contacts: "<<collisionDetector.getContactCount()<<endl;


		collisionDetector.reset();
		collisionDetector.update();
		collisionDetector.detectCollisions(t,h);

		contactHandler.handleContacts(collisionDetector,multiBodyDynamics);

		}
	else {
		contactHandler.clearContactJoints();
		}
	if(doMultiBody)multiBodyDynamics.correctPositions(h);

	}

void DynamicsAlgorithm::postIntegration(Real t,Real h){
	if(doMultiBody)multiBodyDynamics.correctVelocities();
	textilesModule.normalize();
	}

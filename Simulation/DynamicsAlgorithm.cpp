#include "DynamicsAlgorithm.h"
#include "Dynamics\RigidBodyConnector.h"
#include "Visualization\MiniGL.h"
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

	// handle collisions until there are no collisions
	collisionDetector.foreachCollision([](Collision *collision) {
		collision->foreachContact([collision](Contact *contact) {

			if (collision->classifyContact(*contact) == COLLISION) {

				RigidBody *body1 = collision->getObjectA().getRigidBody();
				RigidBody *body2 = collision->getObjectB().getRigidBody();
				if (body1 && body2) {
					Connector *c1 = RigidBodyConnector::createWithWorldConnectionPoint(*body1, contact->pA_wcs);
					Connector *c2 = RigidBodyConnector::createWithWorldConnectionPoint(*body2, contact->pB_wcs);

					// calculateCachedValues is required to get up-to-date velocities
					c1->calculateCachedValues();
					c2->calculateCachedValues();
					const Vector3D &v1 = c1->getWorldVelocity();
					const Vector3D &v2 = c2->getWorldVelocity();

					Vector3D v_rel;
					Vector3D::subtract(v2, v1, v_rel);

					double v_rel_n, delta_v_rel_n;
					Vector3D::dotProduct(v_rel, contact->normal, v_rel_n);
					double combinedElasticity = collision->getObjectA().getElasticityCoefficient() * collision->getObjectB().getElasticityCoefficient();
					////////////////////////////////////////////////////
					delta_v_rel_n = -(combinedElasticity + 1) * v_rel_n;		
					////////////////////////////////////////////////////

					Matrix3x3  K_aa(0);
					Matrix3x3  K_bb(0);

					const Vector3D & a_wcs = c1->getCachedWorldPosition();
					const Vector3D & b_wcs = c2->getCachedWorldPosition();

					c1->getKMatrix(K_aa,a_wcs,a_wcs);
					c2->getKMatrix(K_bb,b_wcs,b_wcs);

					Matrix3x3 K = K_aa + K_bb;

					Vector3D p_a;
					// if the sum of the matrices is 0, do not invert it: use 0 for the inverse matrix, too, instead
					if (K.isZero()) {
						p_a = 0;
						}
					else {
						Real denominator;
						Vector3D::dotProduct(contact->normal, K * contact->normal, denominator);
						Vector3D delta_v;
						Vector3D::multiplyScalar(delta_v_rel_n, contact->normal, delta_v);
						Vector3D::multiplyScalar(-1 / denominator, delta_v, p_a); 
						}
					Vector3D p_b = -p_a;

					Vector3D pos1 = c1->getWorldPosition();
					Vector3D pos2 = c2->getWorldPosition();

					if (pos1 == pos1 && pos2 == pos2) {
						c1->applyImpulse(p_a);
						c2->applyImpulse(p_b);
					}
					}
				}
			});
		});

	}
void DynamicsAlgorithm::postIntegration(Real t,Real h){
	if(doMultiBody)multiBodyDynamics.correctVelocities();
	textilesModule.normalize();
	}

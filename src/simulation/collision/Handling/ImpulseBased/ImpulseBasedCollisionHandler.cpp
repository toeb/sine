#include "ImpulseBasedCollisionHandler.h"
#include <Simulation/Dynamics/Connection/Connector.h>
#include <Simulation/Collision/Handling/ImpulseBased/ContactJoint.h>
#include <Simulation/Dynamics/Connection/ConnectorFactory.h>
#include <Simulation/Collision/Handling/ImpulseBased/DynamicContact.h>

using namespace IBDS;
using namespace std;


ImpulseBasedCollisionHandler::ImpulseBasedCollisionHandler(
	CollisionDetector & detector, ImpulseBasedMultiBodyModule & dynamics):
_detector(detector),_ibdsAlgorithm(dynamics){
  setName("ImpulseBasedCollisionHandler");
	}

void ImpulseBasedCollisionHandler::reset(){
  tick();
	_ibdsAlgorithm.clearTemporaryJoints();
  tock();
}

void ImpulseBasedCollisionHandler::handleCollisions(){
  tick();
	do {	// keep handling collisions until there are none
		_collisionsCount = 0;
		reset();
		detector().foreachCollision([this](Collision * collision){
			if(collision->getObjectA().getType() != DynamicCollidable::type)return;
			if(collision->getObjectB().getType() != DynamicCollidable::type)return;
			DynamicCollidable & collidableA = static_cast<DynamicCollidable&>(collision->getObjectA());
			DynamicCollidable & collidableB = static_cast<DynamicCollidable&>(collision->getObjectB());
			Contact combinedContact;
			collision->combineContacts(combinedContact);

			DynamicContact * contact = new DynamicContact(collidableA,collidableB,combinedContact);
			handleContact(*contact);
			});
		} while (_collisionsCount != 0);
  tock();
}

void ImpulseBasedCollisionHandler::addContactJoint(DynamicContact & contact){
	ContactJoint *joint = new ContactJoint(contact, 10e-4, contact.contact().normal);
	_ibdsAlgorithm.addTemporaryJoint(*joint);	
}

void ImpulseBasedCollisionHandler::handleContact(DynamicContact & dynamicContact){
  Contact & contact = dynamicContact.contact();

	ContactType classification = dynamicContact.classify();
	// if the contact is resting add a joint.
	if (classification == RESTING_CONTACT) {
		addContactJoint(dynamicContact);
		return;
	}

	// if the contact is not a collision (drifting apart or unknwon) return
	if(classification != COLLISION) return;

	//else its a collision
	_collisionsCount++;

	Connector &cA = dynamicContact.connectorA();
	Connector &cB = dynamicContact.connectorB();

  
	const Vector3D & a_wcs = cA.getCachedWorldPosition();
	const Vector3D & b_wcs = cB.getCachedWorldPosition();

  //initialize two matrices and get the K matrix from the connectors
	Matrix3x3  K_aa(0);
	Matrix3x3  K_bb(0);
  
	cA.getKMatrix(K_aa,a_wcs,a_wcs);
	cB.getKMatrix(K_bb,b_wcs,b_wcs);

  //add the two matrices to get the combined matrix
	Matrix3x3 K = K_aa + K_bb;


	Vector3D p_a;
	//if K is zero impulse is zero
  if (K.isZero()) 
  {
		p_a.setZero();
	}
	else 
  {
    //calculate the resulting impulse
		Real denominator;
		Vector3D::dotProduct(contact.normal, K * contact.normal, denominator);

		Vector3D delta_v;
		dynamicContact.getNormalRelativeVelocityVector(delta_v);

		double combinedElasticity = dynamicContact.collidableA().getElasticityCoefficient() * dynamicContact.collidableB().getElasticityCoefficient();

		Vector3D::multiplyScalar(-(combinedElasticity + 1), delta_v, delta_v);
		Vector3D::multiplyScalar(-1 / denominator, delta_v, p_a); 
	}
	
  //apply the impulse
	dynamicContact.applyNormalImpulse(p_a);


}

#include "ImpulseBasedCollisionHandler.h"
#include <Simulation/Dynamics/Connection/Connector.h>
#include <Simulation/Collision/Handling/ImpulseBased/ContactJoint.h>
#include <Simulation/Dynamics/Connection/ConnectorFactory.h>
#include <Simulation/Collision/Handling/ImpulseBased/DynamicContact.h>

using namespace IBDS;
using namespace std;


ImpulseBasedCollisionHandler::ImpulseBasedCollisionHandler(
  CollisionDetector & detector, ImpulseBasedDynamicsAlgorithm & dynamics):
  _detector(detector),_ibdsAlgorithm(dynamics){

}
void ImpulseBasedCollisionHandler::reset(){
  
  _ibdsAlgorithm.clearTemporaryJoints();
  for_each(_dynamicContacts.begin(), _dynamicContacts.end(), [](DynamicContact * contact){
    delete contact;
  });
  _dynamicContacts.clear();
}
void ImpulseBasedCollisionHandler::handleCollisions(){
  reset();
  
  detector().foreachCollision([this](Collision * collision){
    if(collision->getObjectA().getType() != DynamicCollidable::type)return;
    if(collision->getObjectB().getType() != DynamicCollidable::type)return;
    DynamicCollidable & collidableA = static_cast<DynamicCollidable&>(collision->getObjectA());
    DynamicCollidable & collidableB = static_cast<DynamicCollidable&>(collision->getObjectB());
    Contact combinedContact;
    collision->combineContacts(combinedContact);
    
    DynamicContact * contact = new DynamicContact(collidableA,collidableB,combinedContact);
    _dynamicContacts.push_back(contact);
    handleContact(*contact);
  });
}
void ImpulseBasedCollisionHandler::addContactJoint(DynamicContact & contact){
  ContactJoint *joint = new ContactJoint(contact, 10e-4, contact.contact().normal);
  _ibdsAlgorithm.addTemporaryJoint(*joint);	
}
void ImpulseBasedCollisionHandler::handleContact(DynamicContact & contact){

  
  ContactType classification = contact.classify();

  // if the contact is resting add a joint.
  if (classification == RESTING_CONTACT) {
    addContactJoint(contact);
    return;
  }
  // if the contact is not a collision (drifting apart or unknwon) return
  if(classification != COLLISION) return;
  
  //else its a collision
  Connector &cA = contact.connectorA();
  Connector &cB = contact.connectorB();
  
  //increaseCollisionCount();

  Matrix3x3  K_aa(0);
  Matrix3x3  K_bb(0);

  const Vector3D & a_wcs = cA.getCachedWorldPosition();
  const Vector3D & b_wcs = cB.getCachedWorldPosition();

  cA.getKMatrix(K_aa,a_wcs,a_wcs);
  cB.getKMatrix(K_bb,b_wcs,b_wcs);

  Matrix3x3 K = K_aa + K_bb;

  Vector3D p_a;
  if (K.isZero()) {
    p_a.setZero();
  }
  else {
    Real denominator;
    Vector3D::dotProduct(contact.contact().normal, K * contact.contact().normal, denominator);

    Vector3D delta_v;
    contact.getNormalRelativeVelocityVector(delta_v);
    
    double combinedElasticity = contact.collidableA().getElasticityCoefficient() * contact.collidableB().getElasticityCoefficient();
    Vector3D::multiplyScalar(-(combinedElasticity + 1), delta_v, delta_v);

    Vector3D::multiplyScalar(-1 / denominator, delta_v, p_a); 
    }
  Vector3D p_b = -p_a;

  Vector3D pos1 = cA.getWorldPosition();
  Vector3D pos2 = cB.getWorldPosition();

  if (pos1 == pos1 && pos2 == pos2) {
    contact.applyNormalImpulse(p_a);
  }
  
}

#include "Collision.h"
#include "Simulation\Dynamics\Connector.h"
#include "Simulation\Dynamics\RigidBodyConnector.h"
#include "Simulation\Dynamics\RigidBody.h"
#include "Simulation\Dynamics\BodyPrimitives\Sphere.h"
#include "Collidable.h"

using namespace IBDS;
using namespace std;



Collision::~Collision(){

  foreachContact([](Contact * c){
    delete c;
  });
  _contacts.clear();
}

Collision::Collision(ICollidable & a, ICollidable & b):_objectA(a), _objectB(b){

};

int Collision::getContactCount()const{return _contacts.size();}

void Collision::addContact(Contact * contact){
  _contacts.push_back(contact);
}
void Collision::foreachContact(std::function<void (Contact *)> f){
  for_each(_contacts.begin(), _contacts.end(), f);
}

void Collision::combineContacts(Contact & contact){
    
  foreachContact([&contact](Contact * currentContact){
    Vector3D::add(contact.pA_wcs,currentContact->pA_wcs,contact.pA_wcs);
    Vector3D::add(contact.pB_wcs,currentContact->pB_wcs,contact.pB_wcs);
    Vector3D::add(contact.normal,currentContact->normal,contact.normal);
    contact.penetrationDepth += currentContact->penetrationDepth;
  });
    
  Vector3D::multiplyScalar(1.0/_contacts.size(),contact.pA_wcs,contact.pA_wcs );
  Vector3D::multiplyScalar(1.0/_contacts.size(),contact.pB_wcs,contact.pB_wcs );
  contact.penetrationDepth /= _contacts.size();
  contact.normal.normalize();
}


ICollidable & Collision::getObjectA()const{return _objectA;}
ICollidable & Collision::getObjectB()const{return _objectB;}

ContactType Collision::classifyContact(const Contact& contact) {
	RigidBody *body1 = getObjectA().getRigidBody();
	RigidBody *body2 = getObjectB().getRigidBody();
	if (!body1 || !body2) {
		return UNKNOWN;
		}

	Connector *c1 = RigidBodyConnector::createWithWorldConnectionPoint(*body1, contact.pA_wcs);
	Connector *c2 = RigidBodyConnector::createWithWorldConnectionPoint(*body2, contact.pB_wcs);

	// calculateCachedValues is required to get up-to-date velocities
	c1->calculateCachedValues();
	c2->calculateCachedValues();
	const Vector3D &v1 = c1->getWorldVelocity();
	const Vector3D &v2 = c2->getWorldVelocity();

	Vector3D v_rel;
	Vector3D::subtract(v2, v1, v_rel);
	
	double v_rel_n;
	Vector3D::dotProduct(v_rel, contact.normal, v_rel_n);

	double threshold = 10e-3;
	if (v_rel_n >= threshold)
		return DRIFTING_APART;
	else if (v_rel_n > -threshold)
		return RESTING_CONTACT;
	else
		return COLLISION;
}

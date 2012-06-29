#include <Simulation\Collision\Handling\ContactHandler.h>

using namespace IBDS;

void ContactHandler::resetCollisionCount() {
	collisionCount = 0;
	}

void ContactHandler::increaseCollisionCount() {
	collisionCount++;
	}

bool ContactHandler::existCollisions(){
	return collisionCount!=0;
	}

void ContactHandler::addContactJoint(Contact* contact) {
	if (contact->getConnector1() && contact->getConnector2()) {
		ContactJoint *joint = new ContactJoint(contact, 10e-4, contact->normal);
		contactJoints.push_back(joint);
		_multiBodyDynamics->addSimulationObject(joint);
		}
	}

void ContactHandler::clearContactJoints() {
	for (std::vector<ContactJoint*>::iterator it = contactJoints.begin(); it != contactJoints.end(); it++) {
		_multiBodyDynamics->removeSimulationObject(*it);
		}
	contactJoints.clear();
	}

void ContactHandler::handleContact(Collision* collision, Contact* contact) {

	ContactType classification = contact->classify();

	if (classification == RESTING_CONTACT) {
		addContactJoint(contact);
		}

	else if (classification == COLLISION) {
		Connector *c1 = contact->getConnector1();
		Connector *c2 = contact->getConnector2();
		if (!c1 || !c2) return;

		increaseCollisionCount();

		Matrix3x3  K_aa(0);
		Matrix3x3  K_bb(0);

		const Vector3D & a_wcs = c1->getCachedWorldPosition();
		const Vector3D & b_wcs = c2->getCachedWorldPosition();

		c1->getKMatrix(K_aa,a_wcs,a_wcs);
		c2->getKMatrix(K_bb,b_wcs,b_wcs);

		Matrix3x3 K = K_aa + K_bb;

		Vector3D p_a;
		if (K.isZero()) {
			p_a = 0;
			}
		else {
			Real denominator;
			Vector3D::dotProduct(contact->normal, K * contact->normal, denominator);

			Vector3D delta_v;
			contact->getNormalRelativeVelocityVector(delta_v);
			double combinedElasticity = collision->getObjectA().getElasticityCoefficient() * collision->getObjectB().getElasticityCoefficient();
			Vector3D::multiplyScalar(-(combinedElasticity + 1), delta_v, delta_v);

			Vector3D::multiplyScalar(-1 / denominator, delta_v, p_a); 
			}
		Vector3D p_b = -p_a;

		Vector3D pos1 = c1->getWorldPosition();
		Vector3D pos2 = c2->getWorldPosition();

		if (pos1 == pos1 && pos2 == pos2) {
			contact->applyNormalImpulse(p_a);
			}
		}
	}

void ContactHandler::handleContacts(CollisionDetector &collisionDetector, ImpulseBasedDynamicsAlgorithm &multiBodyDynamics) {
	_multiBodyDynamics = &multiBodyDynamics;

	// contact joints exist for the duration of joint position correction only 
	// and must be deleted after they have been processed = before new ones are created
	clearContactJoints();

	// handle contacts until there are no collisions
	do {
		resetCollisionCount();

		collisionDetector.foreachCollision([this](Collision *collision) {
			ContactHandler *this_ = this;
			collision->foreachContact([collision, this_](Contact *contact) {
				this_->handleContact(collision, contact);
				});
			});
		} while (existCollisions());
	}
#pragma once
#include <Simulation/Dynamics/Connector.h>
#include <Simulation/Core/SimulationModuleBase.h>

#include <Simulation\Collision\Contact.h>
#include <Simulation\Collision\Detection\CollisionDetector.h>
#include <SImulation\Collision\Handling\ContactJoint.h>
#include <vector>
#include <Simulation\MultiBodyDynamics\ImpulseBasedDynamicsAlgorithm.h>

namespace IBDS{

	class ContactHandler :public SimulationModuleBase<Contact>{
	private:

		// the number of detected actual collisions (2 bodies actively interpenetrating each other)
		int collisionCount;

		// ContactJoints constructed during the current simulation step
		std::vector<ContactJoint*> contactJoints;

		// reference to the algorithm concerned with joint handling
		ImpulseBasedDynamicsAlgorithm *_multiBodyDynamics;



		void handleContact(Collision* collision, Contact* contact);

		void resetCollisionCount();
		void increaseCollisionCount();
		bool existCollisions();

		void addContactJoint(Contact* contact);
		void clearContactJoints();

	public:

		/**
		 * Handles contacts detected by the collisionDetector, using multiBodyDynamics to handle the introduced contact joints.
		 */
		void handleContacts(CollisionDetector &collisionDetector, ImpulseBasedDynamicsAlgorithm &multiBodyDynamics);

		};

	}
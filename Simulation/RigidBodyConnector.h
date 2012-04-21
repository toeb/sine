#pragma once
#include <Math/Vector3D.h>
#include "Simulation/RigidBody.h"
#include "Simulation/Connector.h"
namespace IBDS {
	/**
	 * Subclass of Connector. Used when a connection point lies on a rigid body.
	 */
	class RigidBodyConnector: public Connector
	{
	private:
		// pointer to the associated rigid body
		RigidBody *_rigidBody;

		// pointer to the position of the connector with respect to the center of mass assuming zero rotation
		Vector3D *_r;

		/**
		 * Returns the current position of the connector with respect to the center of mass.
		 */
		const Vector3D * get_r_new() const;

	public:
		RigidBodyConnector(void);
		~RigidBodyConnector(void);

		/**
		 * Create an instance of this class associated with the rigid body b
		 * \param b pointer to the rigid body to associate this object with.
		 * \param r pointer to the position of the connector with respect to the center of mass
		 */
		RigidBodyConnector(RigidBody *b, Vector3D *r);

		const Vector3D * getPosition()const;
		const Vector3D * getVelocity()const;
		void addExternalForce(const Vector3D &f);
	};
	}
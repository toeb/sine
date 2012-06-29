#pragma once
#include <Math/Vector3D.h>
#include <Simulation\Dynamics\DynamicBody.h>
#include <Simulation\Dynamics\Connector.h>
#include <Simulation\Dynamics\RigidBodyConnector.h>
#include <Simulation\Dynamics\Particle.h>
#include <Simulation\Dynamics\ParticleConnector.h>

namespace IBDS{

	enum ContactType {COLLISION, RESTING_CONTACT, DRIFTING_APART, UNKNOWN};

	class Contact : public ISimulationObject {
	private:
		Connector *_c1;
		Connector *_c2;

		Vector3D _accumulatedImpulse;

		void getRelativeVelocityVector (Vector3D & out);

	public:
		///< the position in world coordinate where object A collides
		Vector3D pA_wcs;
		///< the position in world coordinate where object B collides
		Vector3D pB_wcs;
		///< the collision normal
		Vector3D normal;
		///< The depth of the penetration
		Real penetrationDepth;

		/**
		 * Creates a Contact instance. 
		 * body1 and body2 are the two contacting dynamic bodies (needed to apply collision response),
		 * pA_wcs_in and pB_wcs_in are the coordinates of the respective contact points,
		 * normal_in - the contact normal,
		 * penetrationDepth_in - the depth of the penetration
		 */
		Contact(DynamicBody &body1, DynamicBody &body2, const Vector3D &pA_wcs_in, const Vector3D &pB_wcs_in, const Vector3D &normal_in, Real penetrationDepth_in);

		Contact();
		
		void getNormalRelativeVelocity(Real &out);

		void getNormalRelativeVelocityVector (Vector3D &out);

		ContactType classify();

		Connector* getConnector1();

		Connector* getConnector2();

		/**
		 * Applies the impulse p to the first body and -p to the second body.
		 * If the resulting accumulated impulse would make the bodies stick together, 
		 * an impulse is applied in order to make the accumulated impulse 0.
		 */
		void applyNormalImpulse(Vector3D &p);

		};

	}
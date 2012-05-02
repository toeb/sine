#pragma once
#include <Math/Vector3D.h>
#include "Integrators/IIntegrable.h"
namespace IBDS {
	/**
	 * A connector is a point on a body. It is used to model the points where a spring is attached.
	 */

class Connector : public IIntegrable
	{
	public:
		/**
		 * The position of the connection point
		 */
		virtual const Vector3D * getPosition()const = 0;

		/**
		 * The velocity of the connection point
		 */
		virtual const Vector3D * getVelocity() = 0;
		
		/**
		 * Apply a force to the connection point.
		 * \param the force vector
		 */
		virtual void addExternalForce(const Vector3D &f) = 0;

		/**
		 * This method is called before the integration step t -> t+h of the bodies
		 * but after the integration step t -> t+h of the connectors
		 */
		virtual const Vector3D * getNextPosition(Real h) const = 0;

		virtual void applyImpulse(Vector3D const * const p) = 0;

		virtual Matrix3x3 const * const getKMatrix() const = 0;

	};
	}
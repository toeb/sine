#pragma once
#include <Math/Vector3D.h>
namespace IBDS {
	/**
	 * A connector is a point on a body. It is used to model the points where a spring is attached.
	 */

class Connector
	{
	public:
		/**
		 * The position of the connection point
		 */
		virtual const Vector3D * getPosition()const = 0;

		/**
		 * The velocity of the connection point
		 */
		virtual const Vector3D * getVelocity()const = 0;
		
		/**
		 * Apply a force to the connection point.
		 * \param the force vector
		 */
		virtual void addExternalForce(const Vector3D &f) = 0;
	};
	}
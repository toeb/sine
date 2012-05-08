#pragma once
#include <Math/Vector3D.h>
#include "RigidBody.h"
#include "Connector.h"
#include "Math/SimMath.h"
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
		/*Vector3D *_r;*/
		Vector3D _r;
		Vector3D _rDot;

    Vector3D _rOld;
		/**
		 * Returns the current position of the connector with respect to the center of mass.
		 */
		//const Vector3D * get_r_new() const;

	public:
		~RigidBodyConnector(void);

		/**
		 * Create an instance of this class associated with the rigid body b
		 * \param b pointer to the rigid body to associate this object with.
		 * \param r pointer to the position of the connector with respect to the center of mass
		 */
		RigidBodyConnector(RigidBody *b, Vector3D *r);

    /**
     * \brief Gets the position of the connector in object coordinates
     *
     * \return  The position.
     */
		 const Vector3D &   getPosition()const;

    /**
     * \brief Gets the velocity of the vector in object coordinates.
     *
     * \return  The velocity.
     */
     const Vector3D &   getVelocity()const;


    const Vector3D & calculateWorldPosition()const;
    const Vector3D & calculateWorldVelocity()const;

		void addExternalForce(const Vector3D &f);


		const Vector3D &  getNextPosition(Real h) const;

		void applyImpulse(const Vector3D & p);

		const Matrix3x3 & getKMatrix() const;

		void evaluate();

		void setState(const Real * state);

		void getState(Real * state)const;

		void getDerivedState(Real * xDot)const;

		int getStateDimension()const;

};
}
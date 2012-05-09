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
		// reference to the associated rigid body
		RigidBody & _rigidBody;
		///< The connection vector in object coordinates of the associated body
		Vector3D  _r;
		
    Vector3D _rDot;
    Vector3D _rOld;
    	/**
		 * Create an instance of this class associated with the rigid body b
		 * \param b pointer to the rigid body to associate this object with.
		 * \param r pointer to the position of the connector in object coordinates
		 */
		RigidBodyConnector(RigidBody & b, const Vector3D & r);

	public:
		~RigidBodyConnector(void);


    static RigidBodyConnector * createWithLocalConnectionPoint(RigidBody & body, const Vector3D & r_ocs);
    static RigidBodyConnector * createWithWorldConnectionPoint(RigidBody & body, const Vector3D & r_wcs);

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

    /**
     * \brief Gets the K(r,r) matrix. 
     *
     * \return  The k matrix.
     */
		const Matrix3x3 & getKMatrix() const;

		void evaluate();

		void setState(const Real * state);

		void getState(Real * state)const;

		void getDerivedState(Real * xDot)const;

		int getStateDimension()const;

};
}
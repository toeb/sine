#pragma once
#include <Math/Vector3D.h>
#include <Simulation/Dynamics/RigidBody.h>
#include <Simulation/Dynamics/Connection/Connector.h>
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
		const Vector3D & getObjectCoordinatePosition()const;
      

    void calculateWorldPosition    (Vector3D & p_wcs)const;
    void calculateWorldVelocity    (Vector3D & v_wcs)const;
    void calculateWorldAcceleration(Vector3D & a_wcs)const;


		void addExternalForceToBody(const Vector3D &f);
		void previewPosition(Real h, Vector3D & p_next_wcs) ;
		void applyImpulse(const Vector3D & p);


		void evaluate();
		void setState(const Real * state);
		void getState(Real * state)const;
		void getDerivedState(Real * xDot)const;
		int getStateDimension()const;

};
}
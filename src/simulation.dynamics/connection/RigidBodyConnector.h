#pragma once
#include <math/definitions.h>
#include <simulation.dynamics/RigidBody.h>
#include <simulation.dynamics/connection/Connector.h>
namespace nspace {
	/**
	 * Subclass of Connector. Used when a connection point lies on a rigid body.
	 */
	class RigidBodyConnector: public DynamicConnector
	{
  public:
    Vector3D lastImpulse;
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

    static RigidBodyConnector * createWithLocalConnectionPoint(RigidBody & body, const Vector3D & r_ocs);
    static RigidBodyConnector * createWithWorldConnectionPoint(RigidBody & body, const Vector3D & r_wcs);
	public:    
    friend class ConnectorFactory;
		~RigidBodyConnector(void);


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



};
}
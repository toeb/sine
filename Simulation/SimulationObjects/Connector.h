#pragma once
#include <Math/Vector3D.h>
#include <Simulation/Integrators/IIntegrable.h>
#include <Simulation/SimulationObjects/Body.h>
#include <Visualization/IRenderer.h>
namespace IBDS {
	/**
	 * A connector is a point on a body. It is used to model the points where a spring is attached.
	 */

class Connector : public ISimulationObject
	{
  private:
    ///< The world position (cached)
    Vector3D _worldPosition;
    ///< The world velocity (cached)
    Vector3D _worldVelocity;

    ///< The world acceleration
    Vector3D _worldAcceleration;
    Body & _body;
  public:
    Connector(Body & body);

		/**
		 * The position of the connection point in the body's object coordinates
		 */
		virtual const Vector3D & getObjectCoordinatePosition()const = 0;

		
		/**
		 * Apply a force to the connection point.
		 * \param the force vector in world coordinates
		 */
		virtual void addExternalForce(const Vector3D &f) = 0;

		/**
		 * This method is called before the integration step t -> t+h of the bodies
		 * but after the integration step t -> t+h of the connectors
		 */
		virtual void previewPosition(Real h, Vector3D & p_next_wcs) const = 0;

		virtual void applyImpulse(const Vector3D & p) = 0;
    /**
     * \brief calculates the world position.
     *
     * \return  The world position.
     */
  
    /**
     * \brief Calculates the world velocity.
     *
     * \return  The calculated world velocity.
     */
    
    virtual void calculateWorldPosition(Vector3D & worldPosition)const=0;
    virtual void calculateWorldVelocity(Vector3D & worldVelocity)const=0;
    virtual void calculateWorldAcceleration(Vector3D & worldPosition)const=0;
    
    void calculateCachedValues();
    /**
     * \brief Gets the k matrix. K_{a,b} is the matrix that maps the impulse applied at point a to the impulse
     * 				result at point b of  a rigid body.  
     *
     * \return  The k matrix.
     */
		void getKMatrix(Matrix3x3 & K) const;

    virtual const Vector3D & getWorldPosition()const;

    
    /**
     * \brief Gets the body.
     *
     * \author Tobi
     * \date 09.05.2012
     *
     * \return The body.
     */
    Body & getBody();
    
    const Body & Connector::getBody()const;
	};
	}
#pragma once
#include <Math/Vector3D.h>
#include <Simulation/Integrators/IIntegrable.h>
namespace IBDS {
	/**
	 * A connector is a point on a body. It is used to model the points where a spring is attached.
	 */

class Connector : public IIntegrable
	{
  private:
    Vector3D _worldPosition;
    Vector3D _worldVelocity;
	public:
		/**
		 * The position of the connection point in object coordinates
		 */
		virtual const Vector3D & getPosition()const = 0;

		/**
		 * The velocity of the connection point in object coordinates
		 */
		virtual const Vector3D & getVelocity() const= 0;
		
		/**
		 * Apply a force to the connection point.
		 * \param the force vector
		 */
		virtual void addExternalForce(const Vector3D &f) = 0;

		/**
		 * This method is called before the integration step t -> t+h of the bodies
		 * but after the integration step t -> t+h of the connectors
		 */
		virtual const Vector3D & getNextPosition(Real h) const = 0;

		virtual void applyImpulse(const Vector3D & p) = 0;

    /**
     * \brief Gets the k matrix. K_{a,b} is the matrix that maps the impulse applied at point a to the impulse
     * 				result at point b of  a rigid body.  
     *
     * \return  The k matrix.
     */
		virtual const Matrix3x3 & getKMatrix() const = 0;

    /**
     * \brief calculates the world position.
     *
     * \return  The world position.
     */
  
    virtual const Vector3D & calculateWorldPosition()const=0;
    virtual const Vector3D & getWorldPosition()const{
     return _worldPosition;
    }
    /**
     * \brief Calculates the world velocity.
     *
     * \return  The calculated world velocity.
     */
    virtual const Vector3D & calculateWorldVelocity()const=0;
    virtual const Vector3D & getWorldVelocity()const{
      return _worldVelocity;
    }

      void calculate(){
      _worldPosition = calculateWorldPosition();
      _worldVelocity = calculateWorldVelocity();
    }

	};
	}
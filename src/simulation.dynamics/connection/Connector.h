#pragma once
#include <math/core.h>
#include <simulation.dynamics/DynamicBody.h>

namespace nspace {
  class ConnectorFactory;
  /**
  * A connector is a point on a body. It is used to model the points where a spring is attached.
  */

  class DynamicConnector : public ISimulationObject
  {
  private:
    ///< The world velocity (cached)
    Vector3D _worldVelocity;
    ///< The world acceleration
    Vector3D _worldAcceleration;
    ///< The force acting on this connector
    Vector3D _f;
    DynamicBody & _body;
  protected:
    DynamicConnector(DynamicBody & body);
  public:
    friend class ConnectorFactory;

    /**
    * The position of the connection point in the body's object coordinates
    */
    virtual const Vector3D & getObjectCoordinatePosition()const = 0;

    /**
    * Apply a force to the connection point. (stores the last force added to be displayable)
    * \param the force vector in world coordinates
    */
    virtual void addExternalForce(const Vector3D &f);

    /**
    * \brief actually adds the external force to body.
    *
    *      subclasses must implement
    *
    * \param f The f.
    */
    virtual void addExternalForceToBody(const Vector3D & f)=0;

    const Vector3D & getLastForce()const{
      return _f;
    }
    /**
    * This method is called before the integration step t -> t+h of the bodies
    * but after the integration step t -> t+h of the connectors
    */
    virtual void previewPosition(Real h, Vector3D & p_next_wcs)  = 0;

    virtual void applyImpulse(const Vector3D & p) = 0;

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
    void getKMatrix(Matrix3x3 & K, const Vector3D & a_wcs, const Vector3D& b_wcs) const;

    const Vector3D & getCachedWorldPosition()const;
    const Vector3D & getWorldPosition();

    const Vector3D & getCachedWorldVelocity()const;
    const Vector3D & getWorldVelocity();

    const Vector3D & getCachedWorldAcceleration()const;
    const Vector3D & getWorldAcceleration();

    /**
    * \brief Gets the body.
    *
    * \author Tobi
    * \date 09.05.2012
    *
    * \return The body.
    */
    DynamicBody & body();
    const DynamicBody & body()const;

  protected:
    ///< The world position (cached)
    Vector3D _worldPosition;
  };
}
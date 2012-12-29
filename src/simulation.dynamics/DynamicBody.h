#pragma once
#include <simulation/ISimulationObject.h>
#include <math/core.h>

namespace nspace {
  /**
  * \brief Dynamic body. Interface for Bodies which have mass and thus allow the application of impulses or forces
  *
  *
  */
  class DynamicBody : public virtual ISimulationObject{
  public:

    /**
    * \brief Calculates the dynamics equation.
    *
    */
    virtual void calculateDynamics()=0;

    /**
    * \brief Calculates the cached values.
    *
    */
    virtual void calculateCachedValues()=0;

    //accessors for mass
    virtual Real getMass()const=0;
    virtual void setMass(Real m)=0;

    virtual const Vector3D & getCenterOfGravity()const=0;

    //methods for force / torque access
    virtual void resetForce() = 0;

    virtual void addExternalForce(const Vector3D & f) = 0;
    virtual void addExternalTorque(const Vector3D & tau)=0;

    virtual const Vector3D & getTorque()const =0;
    virtual const Vector3D & getForce()const=0;

    //Impulse access
    virtual void applyImpulse(const Vector3D& a_wcs, const Vector3D& p_wcs)=0;
    virtual void calculateK(Matrix3x3& K, const Vector3D & a_wcs, const Vector3D & b_wcs)const=0;

    virtual const TypeId getBodyType()const =0;

    /**
    * \brief Query if this object is fixed. (which is the case when the mass is 0)
    *
    *
    * \return true if fixed, false if not.
    */
    bool isFixed()const;
  };
}
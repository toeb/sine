#pragma once
#include "Simulation/ISimulationObject.h"
#include <Simulation/Integrators/IIntegrable.h>
#include <Math/Vector3D.h>
namespace IBDS {
	class DynamicBody : public IIntegrable{
  private:
    Vector3D _acceleration;
	public:
	  virtual void resetForce() = 0;
		virtual void addExternalForce(const IBDS::Vector3D & f) = 0;
    virtual void applyImpulse(const Vector3D& a_wcs, const Vector3D& p_wcs)=0;

    virtual const Vector3D & getForce()   const=0;
    virtual const Vector3D & getPosition()const=0;
    virtual const Vector3D & getVelocity()const=0;

    virtual void calculateDynamics()=0;
    virtual void calculateCachedValues(){};

    /**
     * \brief Gets the acceleration
     * 				
     *
     * \author Tobi
     * \date 09.05.2012
     *
     * \return The acceleration.
     */
    const Vector3D & getAcceleration()const;

    void calculateAcceleration();


    /**
     * \brief Gets the mass of this body.
     *
     * \author Tobi
     * \date 10.05.2012
     *
     * \return The mass.
     */
    virtual Real getMass()const = 0;


    /**
     * \brief Calculates the K Matrix. 
     *
     * \author Tobi
     * \date 09.05.2012
     *
     * \param a point a in World Coordinates
     * \param b point b in Wolrd Coordinates
     *
     * \return The calculated k.
     */
    virtual void calculateK(Matrix3x3& K, const Vector3D & a_wcs, const Vector3D & b_wcs)const=0;

    /**
     * \brief Previews position of the center of gravity in h seconds.
     *
     * \author Tobi
     * \date 09.05.2012
     *
     * \param h The timestep.
     *
     * \return the approximated position .
     */
    void previewPosition(Real h, Vector3D& s_next_wcs)const;
  };
}
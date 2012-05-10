#pragma once
#include <Math/Vector3D.h>
#include "Particle.h"
#include "Connector.h"
namespace IBDS {
	/**
	 * Subclass of Connector. Used when a connection point lies on a particle.
	 */
	class ParticleConnector:public Connector
	{
	private:
		// pointer to the associated particle
		Particle & _particle;
  public:
		~ParticleConnector(void);

		/**
		 * Create an instance of this class associated with p
		 * \param p pointer to the particle to associate this object with.
		 */
		ParticleConnector(Particle &p);

		const Vector3D &  getObjectCoordinatePosition()const;
		void addExternalForce(const Vector3D &f);		
		void previewPosition(Real h, Vector3D & p_next_wcs) const;
		void applyImpulse(const Vector3D & p);


    
    /**
     * \brief calculates the world position.
     *
     * \return  The world position.
     */
   void calculateWorldPosition(Vector3D & p_wcs)const;

    /**
     * \brief Calculates the world velocity.
     *
     * \return  The calculated world velocity.
     */
    void calculateWorldVelocity(Vector3D & b_wcs)const;
    void calculateWorldAcceleration(Vector3D & a_wcs)const;
	};
}
#pragma once
#include <math/definitions.h>
#include <simulation/dynamics/Particle.h>
#include <simulation/dynamics/connection/Connector.h>

namespace nspace {
	/**
	 * Subclass of Connector. Used when a connection point lies on a particle.
	 */
	class ParticleConnector:public DynamicConnector
	{
	private:
		// pointer to the associated particle
		Particle & _particle;
		/**
		 * Create an instance of this class associated with p
		 * \param p pointer to the particle to associate this object with.
		 */
		ParticleConnector(Particle &p);
  public:
    friend class ConnectorFactory;
		~ParticleConnector(void);


		const Vector3D &  getObjectCoordinatePosition()const;
		void addExternalForceToBody(const Vector3D &f);		
		void previewPosition(Real h, Vector3D & p_next_wcs) ;
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
    inline void calculateWorldVelocity(Vector3D & b_wcs)const;
    void calculateWorldAcceleration(Vector3D & a_wcs)const;

	  void setWorldPosition(Vector3D &position);
	};
}
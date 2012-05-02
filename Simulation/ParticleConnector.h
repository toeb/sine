#pragma once
#include <Math/Vector3D.h>
#include "Simulation/Particle.h"
#include "Simulation/Connector.h"
namespace IBDS {
	/**
	 * Subclass of Connector. Used when a connection point lies on a particle.
	 */
	class ParticleConnector:public Connector
	{
	private:
		// pointer to the associated particle
		Particle *_particle;
		
		ParticleConnector(void);

	public:
		~ParticleConnector(void);

		/**
		 * Create an instance of this class associated with p
		 * \param p pointer to the particle to associate this object with.
		 */
		ParticleConnector(Particle *p);

		const Vector3D * getPosition()const;

		const Vector3D * getVelocity();
		
		void addExternalForce(const Vector3D &f);

		
		const Vector3D * getNextPosition(Real h) const;

		void applyImpulse(Vector3D const * const p);

		Matrix3x3 const * const getKMatrix() const;

		void evaluate();

		void setState(const Real * state);

		void getState(Real * state)const;

		void getDerivedState(Real * xDot)const;

		int getStateDimension()const;

	};
	}
#pragma once
#include "Simulation/ISimulationObject.h"
#include "Simulation/Body.h"
#include "Simulation/RigidBody.h"
#include "Simulation/Particle.h"
#include "Visualization/MiniGL.h"
#include "Simulation/Connector.h"
#include "Simulation/Force.h"
#include <Vector>

namespace IBDS{
	class DampedSpring : public Force
		{
		private:
			// the points the spring is attached to
			Connector* _c1, *_c2;

			// the world coordinates of the connectors
			Vector3D a, b;

			// stiffness constant
			Real _k_s;
			
			// damping constant
			Real _k_d;
			
			Real _restLength;

			DampedSpring(void);
		public:
			~DampedSpring(void);

			/**
			 * Creates a string with the specified stiffness, damping and rest length, which is attached to the specified connectors.
			 */
			DampedSpring(Connector *c1, Connector *c2, Real k_s, Real k_d, Real restLength);
			
			// Side effect: fields a, b are set.
			void act (std::vector<Body*> & target, Real time);

			virtual void render() const;

		};
	}
#pragma once
#include <Simulation/ISimulationObject.h>
#include "Body.h"
#include "RigidBody.h"
#include "Particle.h"
#include "Visualization/MiniGL.h"
#include "Connector.h"
#include "Force.h"
#include <Vector>
#include <Visualization/IRenderer.h>

namespace IBDS{
	class DampedSpring : public Force, public IRenderer
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

			virtual void render();

		};
	}
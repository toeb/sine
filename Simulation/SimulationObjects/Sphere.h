#pragma once

#include <Simulation/SimulationObjects/RigidBody.h>
#include <Math/Matrix3x3.h>
#include "Visualization/MiniGL.h"
#include <Visualization/IRenderer.h>

namespace IBDS{
	class Sphere: public RigidBody, public IRenderer
		{
		private:
			
			// mass
			Real _m;
			
			// radius
			Real _r;
			
			Sphere();
		public:
			
			~Sphere();
			
			/**
			 *  Creates a sphere with given mass and radius.
			 * \param m mass
			 * \param r radius
			 */
			Sphere(Real m, Real r);

			void render();
		};
	}
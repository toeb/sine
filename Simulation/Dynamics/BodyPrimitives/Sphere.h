#pragma once

#include <Simulation/Dynamics/RigidBody.h>

namespace IBDS{
	class Sphere: public RigidBody
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

		};
	}
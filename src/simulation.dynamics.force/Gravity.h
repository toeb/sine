#pragma once

#include <math/definitions.h>
#include <simulation.dynamics.force/Force.h>
#include <vector>

namespace nspace{
	class Gravity : public Force
		{
		private:
      Vector3D _direction;
      Real _amount;
      Vector3D _g;
      void calculateGravity();
		public:
			~Gravity(void);

			/**
			 * Creates a gravity force with a default gravity coefficient 9.81
			 */
			Gravity(void);
		
			/**
			 * Creates a gravity force with a custom gravity coefficient.
			 * \param g gravity coefficient
			 */
			Gravity(Real g);
			Gravity(const Vector3D & g);

      const Vector3D& getDirection()const;
      void setDirection(const Vector3D & dir);

			void setGravityMagnitude(Real g);
      Real getGravityMagnitude()const;

      void setGravity(const Vector3D & g);
      const Vector3D& getGravity()const;


			void act (std::vector<DynamicBody*> & target, Real time);

		};
	}
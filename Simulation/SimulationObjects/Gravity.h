#pragma once
#include "Body.h"
#include "Math/Vector3D.h"
#include "Force.h"
#include <Vector>

namespace IBDS{
	class Gravity : public Force
		{
		private:
      Vector3D _g;
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
			
      void setGravity(const Vector3D & g);

			void act (std::vector<Body*> & target, Real time);

		};
	}
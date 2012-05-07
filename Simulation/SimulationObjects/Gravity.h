#pragma once
#include "Body.h"
#include "Math/Vector3D.h"
#include "Force.h"
#include <Vector>

namespace IBDS{
	class Gravity : public Force
		{
		private:
			Real _g;
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
			
			void act (std::vector<Body*> & target, Real time);

			virtual void render() const;
		};
	}
#ifndef _BOX_H
#define _BOX_H

#include "Simulation/RigidBody.h"
#include <Math/Matrix3x3.h>
#include "Visualization/MiniGL.h"

namespace IBDS{
	class Box: public RigidBody
		{
		private:
			Real _x, _y, _z;
		public:
			Box();
			~Box();
			Box(Real m, Real x, Real y, Real z);
			void render() const;
		};
	}

#endif 
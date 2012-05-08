#ifndef _BOX_H
#define _BOX_H

#include "RigidBody.h"
#include <Math/Matrix3x3.h>
#include "Visualization/MiniGL.h"
#include <Visualization/IRenderer.h>

namespace IBDS{
	class Box: public RigidBody, public IRenderer
		{
		private:
			// size of the box
			Real _x, _y, _z;
			Box();
		public:
			
			~Box();
			/**
			 *  Creates a box with given mass and extents.
			 * \param m mass
			 * \param x width
			 * \param y height
			 * \param z depth
			 */
			Box(Real m, Real x, Real y, Real z);
    
			void render();
		};
	}

#endif 
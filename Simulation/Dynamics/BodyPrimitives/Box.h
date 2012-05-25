#ifndef _BOX_H
#define _BOX_H

#include <Simulation\Dynamics\RigidBody.h>
#include <Math/Matrix3x3.h>
#include <Simulation/Geometry/Primitives/Hexahedron.h>

namespace IBDS{
class DynamicBox: public virtual RigidBody, public virtual Hexahedron
	{
  public:
		~DynamicBox();

		DynamicBox(Real m, Real x, Real y, Real z);
	};
}

#endif 
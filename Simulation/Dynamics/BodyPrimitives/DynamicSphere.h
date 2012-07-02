#pragma once

#include <Simulation/Geometry/Primitives/Sphere.h>
#include <Simulation/Dynamics/BodyPrimitives/DynamicGeometry.h>

namespace IBDS{

class DynamicSphere: public DynamicGeometry<Sphere>
{
public:
			

	/**
		*  Creates a sphere with given mass and radius.
		* \param m mass
		* \param r radius
		*/
	DynamicSphere(Real m=1, Real r=1);
  static Matrix3x3 calculateInertia(Real m, Real r);

};
}
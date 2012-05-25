#pragma once

#include <Simulation/Dynamics/RigidBody.h>
#include <Simulation/Geometry/Primitives/Sphere.h>
namespace IBDS{
class DynamicSphere: public virtual RigidBody, public virtual Sphere
{
public:
			
	~DynamicSphere();
			
	/**
		*  Creates a sphere with given mass and radius.
		* \param m mass
		* \param r radius
		*/
	DynamicSphere(Real m, Real r);

};
}
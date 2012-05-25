#pragma once
#include <Simulation/Dynamics/RigidBody.h>
#include <Math/Vector3D.h>
namespace IBDS {
class BoundingSphere {
	
private:
	const RigidBody & _body;
	const Vector3D & _centerPos_ocs;
	Real _radius;
	
public:
	BoundingSphere(const RigidBody & body);
	~BoundingSphere();
	
	bool isIntersecting(const BoundingSphere & other) const;
	bool isIntersectingFloor() const;
	const Vector3D & getWorldCenterPosition() const;
};
}
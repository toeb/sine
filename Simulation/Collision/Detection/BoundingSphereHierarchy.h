#pragma once
#include <Simulation/Collision/Detection/BoundingSphere.h>
#include <Simulation/Dynamics/BodyPrimitives/Box.h>
namespace IBDS {
class BoundingSphereHierarchy {
	
private:
	const BoundingSphere & _thisNode;
	bool _isLeaf;
	BoundingSphereHierarchy const * const * const _children;
	int _childrenCount;
	
public:
	BoundingSphereHierarchy(const Box & box, int hierarchyDepth);
	~BoundingSphereHierarchy();
	
	bool isLeaf() const;
	BoundingSphereHierarchy const * const * const getChildren();
	bool isIntersecting(BoundingSphereHierarchy & other) const;
	
};
}
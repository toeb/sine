#pragma once
#include <simulation.geometry/boundingVolumes/BoundingOctree.h>
#include <simulation.geometry/boundingVolumes/BoundingSphere.h>
#include <simulation.collision.test/CollisionTest.h>
#include <simulation.collision.test/SpherePlane.h>

namespace nspace{
class OctreePlane : public CollisionTest{
private:
  SpherePlane test;
public:
  OctreePlane():CollisionTest(Octree::ClassType(),Plane::ClassType()){}
  bool testCollision(const ISimulationObject & a, const ISimulationObject & b, Collision * collision)const;
  bool testCollision(const Octree & a, const Plane & b, Collision * collision)const;

};


}
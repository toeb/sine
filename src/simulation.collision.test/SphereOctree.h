#pragma once
#include <simulation.collision.test/CollisionTest.h>
#include <simulation.collision.test/SphereSphere.h>
#include <simulation.geometry/boundingVolumes/BoundingOctree.h>
#include <simulation.geometry/boundingVolumes/BoundingSphere.h>

namespace nspace{
  class SphereOctree : public CollisionTest{
  private:
    SphereSphere test;
  public:
    SphereOctree():CollisionTest(typeof(Sphere)->getId(),typeof(Octree)->getId()){}
    bool testCollision(const ISimulationObject & a, const ISimulationObject & b, Collision * collision)const;
    bool testCollision(const Sphere & a, const Octree & b, Collision * collision)const;
  };
}
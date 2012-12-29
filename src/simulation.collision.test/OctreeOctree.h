#pragma once
#include <simulation.collision.test/CollisionTest.h>
#include <simulation.collision.test/SphereSphere.h>

#include <simulation.geometry/boundingVolumes/BoundingOctree.h>
#include <simulation.geometry/boundingVolumes/BoundingSphere.h>

namespace nspace{
  class OctreeOctree : public CollisionTest{
  private:
    ///< The sphere test (the octrees bounding volumes are statically represented as spheres)
    SphereSphere sphereTest;
  public:
    OctreeOctree():CollisionTest(Octree::type,Octree::type){}

    bool testCollision(const ISimulationObject & a, const ISimulationObject & b, Collision * collision)const;

    /**
    * \brief Tests collision.
    *
    * \param a                  Octree a.
    * \param b                  Octree b.
    * \param [in,out] collision If non-null, the collision parameters.
    *
    * \return true iff a and b collide.
    */
    bool testCollision(const Octree & a, const Octree & b, Collision * collision)const;
  };
}
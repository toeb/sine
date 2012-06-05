#pragma once
#include <Simulation/Collision/Detection/CollisionTest/CollisionTest.h>
#include <Simulation/Collision/Detection/Acceleration/Octree.h>
#include <Simulation/Collision/Detection/CollisionTest/SphereSphere.h>
#include <Simulation/Geometry/BoundingVolumes/BoundingSphere.h>

namespace IBDS{
class OctreeOctree : public CollisionTest{
private:
  ///< The sphere test (the octrees bounding volumes are statically represented as spheres)
  SphereSphere sphereTest;
public:

  /**
   * \brief returns Octree::type
   * \return The type a.
   */
  const TypeId getTypeA()const;
  /**
   * \brief returns Octree::type
   * \return The type b.
   */
  const TypeId getTypeB()const;

  /**
   * \brief Tests collision.
   *
   * \param a                  Collidable a.  - needs to by of type octree (static cast involved)
   * \param b                  Collidable b.  -  "                  "                  "
   * \param [in,out] collision If non-null, the collision parameters.
   *
   * \return true iff a and b collide.
   */
  bool testCollision(const ICollidable & a, const ICollidable & b, Collision * collision)const;

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
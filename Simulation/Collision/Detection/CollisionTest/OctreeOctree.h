#pragma once

#include <Simulation/Collision/Detection/Acceleration/Octree.h>
#include <Simulation/Collision/Collision.h>
#include "SphereSphere.h"

namespace IBDS{
struct OctreeOctree{
public:
  SphereSphere sphereTest;

  bool testCollision(const Octree & a, const Octree & b, Collision * collision)const;
};
}
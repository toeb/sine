#pragma once

#include <Simulation/Collision/Detection/CollisionDetector.h>
#include <Simulation/Collision/Detection/CollisionTest/SphereSphere.h>
#include <Simulation/Collision/Detection/CollisionTest/OctreeOctree.h>


namespace IBDS{
class OctreeCollisionDetector:public CollisionDetector{
  OctreeOctree collisionTest;
public:
  void detectCollisions(Real time, Real h);
protected:
  bool acceptObject(Collidable * c);
};
}
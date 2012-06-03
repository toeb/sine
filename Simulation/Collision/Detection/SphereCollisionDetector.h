#pragma once

#include <Simulation/Collision/Detection/CollisionDetector.h>
#include <Simulation/Collision/Detection/CollisionTest/SphereSphere.h>


namespace IBDS{
class SphereCollisionDetector:public virtual CollisionDetector{
  SphereSphere collisionTest;
public:
  void detectCollisions(Real time, Real h);
protected:
  bool acceptObject(ICollidable* collidable);
};
}
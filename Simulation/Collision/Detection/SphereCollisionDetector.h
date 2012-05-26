#pragma once

#include <Simulation/Collision/Detection/CollisionDetector.h>
#include <Simulation/Collision/Detection/CollisionTest/SphereSphere.h>


namespace IBDS{
class SphereCollisionDetector:public virtual CollisionDetector{
  SphereSphere collisionTest;
public:
  int detectCollisions();
protected:
  bool acceptObject(Collidable* collidable);
};
}
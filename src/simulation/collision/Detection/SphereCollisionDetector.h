#pragma once

#include <Simulation/Collision/Detection/CollisionDetector.h>
#include <Simulation/Collision/Detection/CollisionTest/SphereSphere.h>


namespace IBDS{
class SphereCollisionDetector:public virtual CollisionDetector{
  SphereSphere collisionTest;
protected:
  void doCollisionDetection(Real time, Real h);
  bool acceptObject(ICollidable* collidable);
};
}
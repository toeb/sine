#pragma once

#include <Simulation/Collision/Detection/CollisionDetector.h>
#include <Simulation/Collision/Detection/CollisionTest/SphereSphere.h>


namespace IBDS{
class SphereCollisionDetector:public virtual CollisionDetector{
  SphereSphere collisionTest;
  std::vector<CollisionSphere*> _spheres;
public:
  int detectCollisions();
protected:
  void onObjectAdded(Collidable* collidable);
  void onObjectRemoved(Collidable * collidable);
};
}
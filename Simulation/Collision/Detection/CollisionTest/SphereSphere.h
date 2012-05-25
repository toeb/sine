#pragma once
#include <Simulation/Collision/Collision.h>
#include <Simulation/Collision/CollisionPrimitives/CollisionSphere.h>

namespace IBDS{
struct SphereSphere{
public:
  CollisionSphere * _A;
  CollisionSphere * _B;
  bool testCollision(Collision & col)const;
};
}
#pragma once
#include <Simulation/Collision/Detection/CollisionTest/CollisionTest.h>
#include <Simulation/Collision/Detection/CollisionDetector.h>
namespace IBDS{

class CompositeCollisionDetector : public CollisionDetector{
public:
  CompositeCollisionDetector();
  void detectCollisions(Real time, Real h);
protected:
  bool accepts(ICollidable * c);
};
}
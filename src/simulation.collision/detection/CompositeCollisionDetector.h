#pragma once
#include <Simulation/Collision/Detection/CollisionTest/CollisionTest.h>
#include <Simulation/Collision/Detection/CollisionDetector.h>
namespace IBDS{

class CompositeCollisionDetector : public CollisionDetector{
public:
  CompositeCollisionDetector();
protected:
  void doCollisionDetection(Real time, Real h);
  bool accepts(ICollidable * c);
};
}
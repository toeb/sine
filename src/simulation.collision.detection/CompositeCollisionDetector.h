#pragma once
#include <simulation.collision.test/CollisionTest.h>
#include <simulation.collision.detection/CollisionDetector.h>
namespace nspace{

class CompositeCollisionDetector : public CollisionDetector{
public:
  CompositeCollisionDetector();
protected:
  void doCollisionDetection(Real time, Real h);
  bool accepts(ICollidable * c);
};
}
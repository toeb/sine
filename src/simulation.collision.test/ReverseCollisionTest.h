#pragma once
#include <simulation.collision.test/CollisionTest.h>

namespace nspace{
  class ReverseCollisionTest : public CollisionTest{
  private:
    CollisionTest & forwardTest;
  public:
    ReverseCollisionTest(CollisionTest & test);
    const TypeId getTypeA()const;
    const TypeId getTypeB()const;
    bool testCollision(const ISimulationObject & a, const ISimulationObject & b, Collision * collision)const;
  };
}
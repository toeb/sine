#pragma once
#include <Simulation/Collision/Detection/CollisionTest/CollisionTest.h>
#include <Simulation/Collision/Collidable.h>
#include <map>
namespace IBDS{
class CollisionTestRepository{
private:
  std::vector<const CollisionTest*> _tests;

  CollisionTestRepository();
public:
  static CollisionTestRepository & instance();
  void addTest(const CollisionTest* test);
  const CollisionTest* getTest(const ISimulationObject & a,const ISimulationObject & b)const;
  const CollisionTest* getTest(const TypeId a,const TypeId b)const;
  const CollisionTest* getTest(const ICollidable & a, const ICollidable & b)const;
  bool hasTest(const ISimulationObject & a,const ISimulationObject & b);
  bool hasTestFor(const ISimulationObject & a)const;
  bool hasTestFor(const ICollidable & collidable)const;
  bool hasTestFor(const TypeId a)const;
};
}
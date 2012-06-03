#pragma once
#include <Simulation/Collision/Detection/CollisionTest/CollisionTest.h>
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
  bool hasTest(const ISimulationObject & a,const ISimulationObject & b);
  bool hasTestFor(const ISimulationObject & a)const;
};
}
#pragma once
#include <Simulation/Collision/Detection/CollisionTest/CollisionTest.h>
#include <map>
namespace IBDS{
class CollisionTestFactory{
private:
  std::vector<const CollisionTest*> _tests;

  CollisionTestFactory();
public:
  static CollisionTestFactory * instance();
  void addTest(const CollisionTest* test);
  const CollisionTest* getTest(const ISimulationObject & a,const ISimulationObject & b)const;
  const CollisionTest* getTest(const TypeId a,const TypeId b)const;
  bool hasTest(const ISimulationObject & a,const ISimulationObject & b);
};
}
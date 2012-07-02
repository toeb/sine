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

  
  const inline CollisionTest* CollisionTestRepository::getTest(const TypeId a,const TypeId b)const{
    const CollisionTest * current=0;
    for(int i=0; i < _tests.size(); i++){
      current = _tests.at(i);
      if(current->getTypeA()==a && current->getTypeB()==b){
        return current;
      }
    }
    return 0;
  }

  const CollisionTest* getTest(const ISimulationObject & a,const ISimulationObject & b)const;


  const inline CollisionTest * operator()(const TypeId a,const TypeId b)const{return getTest(a,b);}
  const inline CollisionTest * operator()(const ISimulationObject & a,const ISimulationObject & b)const{return getTest(a,b);}

  bool hasTest(const ISimulationObject & a,const ISimulationObject & b);
  bool hasTestFor(const ISimulationObject & a)const;
  bool hasTestFor(const TypeId a)const;
};
}
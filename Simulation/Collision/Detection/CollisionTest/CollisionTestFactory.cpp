#include "CollisionTestFactory.h"

#include <Simulation/Collision/Detection/CollisionTest/OctreeOctree.h>
#include <Simulation/Collision/Detection/CollisionTest/SphereSphere.h>
#include <Simulation/Collision/Detection/CollisionTest/SpherePlane.h>
#include <Simulation/Collision/Detection/CollisionTest/SeparatingAxes.h>


using namespace IBDS;

CollisionTestFactory::CollisionTestFactory(){
  addTest(new OctreeOctree());
  addTest(new SphereSphere());
  addTest(new SpherePlane());
  addTest(new SeparatingAxes());  
}


CollisionTestFactory * CollisionTestFactory::instance(){
  static CollisionTestFactory * instance = new CollisionTestFactory();
  return instance;
}

void CollisionTestFactory::addTest(const CollisionTest* test){
  if(getTest(test->getTypeA(),test->getTypeB())){
   return; 
  }
  _tests.push_back(test);
}

const CollisionTest* CollisionTestFactory::getTest(const TypeId a,const TypeId b)const{
  const CollisionTest * current=0;
  for(int i=0; i < _tests.size(); i++){
    current = _tests.at(i);
    if(current->getTypeA()==a && current->getTypeB()==b){
      return current;
    }
  }
  return 0;
}

const CollisionTest* CollisionTestFactory::getTest(const ISimulationObject & a,const ISimulationObject & b)const{
  return getTest(a.getType(),b.getType());
}

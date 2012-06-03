#include "CollisionTestFactory.h"

#include <Simulation/Collision/Detection/CollisionTest/OctreeOctree.h>
#include <Simulation/Collision/Detection/CollisionTest/PlaneOctree.h>
#include <Simulation/Collision/Detection/CollisionTest/SphereOctree.h>
#include <Simulation/Collision/Detection/CollisionTest/ReverseCollisionTest.h>
#include <Simulation/Collision/Detection/CollisionTest/SphereSphere.h>
#include <Simulation/Collision/Detection/CollisionTest/SpherePlane.h>
#include <Simulation/Collision/Detection/CollisionTest/SeparatingAxes.h>


using namespace IBDS;

CollisionTestRepository::CollisionTestRepository(){
  addTest(new OctreeOctree());
  addTest(new SphereSphere());
  addTest(new SpherePlane());
  addTest(new ReverseCollisionTest(*(new SpherePlane())));
  addTest(new OctreePlane());  
  addTest(new ReverseCollisionTest(*(new OctreePlane())));
  addTest(new SphereOctree());
  addTest(new ReverseCollisionTest(*(new SphereOctree())));
  addTest(new SeparatingAxes());  
}


CollisionTestRepository & CollisionTestRepository::instance(){
  static CollisionTestRepository * instance = new CollisionTestRepository();
  return *instance;
}

void CollisionTestRepository::addTest(const CollisionTest* test){
  if(getTest(test->getTypeA(),test->getTypeB())){
   return; 
  }
  _tests.push_back(test);
}

const CollisionTest* CollisionTestRepository::getTest(const TypeId a,const TypeId b)const{
  const CollisionTest * current=0;
  for(int i=0; i < _tests.size(); i++){
    current = _tests.at(i);
    if(current->getTypeA()==a && current->getTypeB()==b){
      return current;
    }
  }
  return 0;
}

bool CollisionTestRepository::hasTestFor(const ISimulationObject & a)const{
  const CollisionTest * current=0;
  for(int i=0; i < _tests.size(); i++){
    current = _tests.at(i);
    TypeId t1 = a.getType();
    TypeId t2 = current->getTypeA();
    TypeId t3 = current->getTypeB();
    if(current->getTypeA()==a.getType() || current->getTypeB()==a.getType()){
      return true;
    }
  }
  return false;
}

const CollisionTest* CollisionTestRepository::getTest(const ISimulationObject & a,const ISimulationObject & b)const{
  return getTest(a.getType(),b.getType());
}

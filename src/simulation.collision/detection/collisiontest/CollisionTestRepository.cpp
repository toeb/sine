#include "CollisionTestRepository.h"

#include <Simulation/Collision/Detection/CollisionTest/OctreeOctree.h>
#include <Simulation/Collision/Detection/CollisionTest/PlaneOctree.h>
#include <Simulation/Collision/Detection/CollisionTest/SphereOctree.h>
#include <Simulation/Collision/Detection/CollisionTest/ReverseCollisionTest.h>
#include <Simulation/Collision/Detection/CollisionTest/SphereSphere.h>
#include <Simulation/Collision/Detection/CollisionTest/SpherePlane.h>
#include <Simulation/Collision/Detection/CollisionTest/SeparatingAxes.h>


using namespace IBDS;

CollisionTestRepository::CollisionTestRepository(){
  addTest(new SphereSphere());
  addTest(new SpherePlane());
  addTest(new OctreeOctree());
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


bool CollisionTestRepository::hasTestFor(const ISimulationObject & a)const{
  return hasTestFor(a.getType());
}


bool CollisionTestRepository::hasTestFor(const TypeId  a)const{
  const CollisionTest * current=0;
  for(int i=0; i < _tests.size(); i++){
    current = _tests.at(i);
    if(current->getTypeA()==a || current->getTypeB()==a){
      return true;
    }
  }
  return false;
}

const CollisionTest* CollisionTestRepository::getTest(const ISimulationObject & a,const ISimulationObject & b)const{
  return getTest(a.getType(),b.getType());
}

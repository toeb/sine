#include "CollisionTestRepository.h"

#include <simulation.collision.test/OctreeOctree.h>
#include <simulation.collision.test/PlaneOctree.h>
#include <simulation.collision.test/SphereOctree.h>
#include <simulation.collision.test/ReverseCollisionTest.h>
#include <simulation.collision.test/SphereSphere.h>
#include <simulation.collision.test/SpherePlane.h>
#include <simulation.collision.test/SeparatingAxes.h>

using namespace nspace;

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
  return hasTestFor(a.getType().getId());
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
  return getTest(a.getType().getId(),b.getType().getId());
}
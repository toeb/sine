#include "CompositeCollisionDetector.h"
#include <Simulation/Collision/Detection/CollisionTest/CollisionTestRepository.h>
using namespace IBDS;
using namespace std;

CompositeCollisionDetector::CompositeCollisionDetector(){
}

void CompositeCollisionDetector::doCollisionDetection(Real time, Real h){
  //iterate through all potential collisions
  foreachPotentialCollision([this](ICollidable * a,ICollidable * b){
    const CollisionTest * test = CollisionTestRepository::instance().getTest(a->getCollisionType(),b->getCollisionType());
    if(test){
      Collision * collision = new Collision(*a,*b);
      if(test->testCollision(*a,*b,collision)){
        addCollision(collision);
      }else{
        delete collision;
      }
    }else{
      cout << "No test found for "<<a->getCollisionType() << " vs. "<< b->getCollisionType() <<endl;
    }
  });
}
  

bool CompositeCollisionDetector::accepts(ICollidable * c){
  return CollisionTestRepository::instance().hasTestFor(*c);
}


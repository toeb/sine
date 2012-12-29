#include "CompositeCollisionDetector.h"
#include <simulation.collision.test/CollisionTestRepository.h>
using namespace nspace;
using namespace std;

CompositeCollisionDetector::CompositeCollisionDetector(){
}

void CompositeCollisionDetector::doCollisionDetection(Real time, Real h){
  //iterate through all potential collisions
  CollisionTestRepository & repository = CollisionTestRepository::instance();
  foreachPotentialCollision([this,&repository](ICollidable * a,ICollidable * b){
    const CollisionTest * test = repository(a->getCollisionType(),b->getCollisionType());
    if(test){
      Collision * collision = Collision::create(*a,*b);
      if(test->testCollision(a->collisionObject(),b->collisionObject(),collision)){
        addCollision(collision);
      }else{
        Collision::freeCollision(collision);
      }
    }else{
      cout << "No test found for "<<a->getCollisionType() << " vs. "<< b->getCollisionType() <<endl;
    }
  });
}

bool CompositeCollisionDetector::accepts(ICollidable * c){
  bool result=  CollisionTestRepository::instance().hasTestFor(c->getCollisionObjectType());
  //explicit: for debugging ...
  if(result){
    return true;
  }else{
    return false;
  }
}
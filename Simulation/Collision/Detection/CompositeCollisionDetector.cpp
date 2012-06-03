#include "CompositeCollisionDetector.h"
#include <Simulation/Collision/Detection/CollisionTest/CollisionTestFactory.h>
using namespace IBDS;
using namespace std;

CompositeCollisionDetector::CompositeCollisionDetector(){
}

void CompositeCollisionDetector::detectCollisions(Real time, Real h){
  resetCollisions();
  foreachPotentialCollision([this](ICollidable * a,ICollidable * b){
    const CollisionTest * test = CollisionTestRepository::instance().getTest(*a,*b);
    if(test){
      //cout << test->getTypeA() << " " <<test->getTypeB() << endl;
      Collision * collision = new Collision(*a,*b);
      if(test->testCollision(*a,*b,collision)){
        addCollision(collision);
      }else{
        delete collision;
      }
    }else{
      cout << "No test found for "<<a->getType() << " vs. "<< b->getType() <<endl;
    }
  });
}
  

bool CompositeCollisionDetector::accepts(ICollidable * c){
  return CollisionTestRepository::instance().hasTestFor(*c);
}


#include "CollisionDetector.h"

using namespace std;
using namespace nspace;

CollisionDetector::CollisionDetector(){
  setName("CollisionDetector");
}

void CollisionDetector::detectCollisions(Real t, Real h){
  tick();
  resetCollisions();
  doCollisionDetection(t,h);
  tock();
}

int CollisionDetector::getContactCount(){
  int count=0;
  for_each(_collisions.begin(), _collisions.end(), [&count](Collision* c){
    count+=c->getContactCount();
  });
  return count;
}
int CollisionDetector::getCollisionCount(){
  return _collisions.size();
}

const vector<Collision*>& CollisionDetector::getCollisions()const{
  return _collisions;
}

void CollisionDetector::resetCollisions(){
  for_each(_collisions.begin(), _collisions.end(), [](Collision* c){
    delete c;
  });
  _collisions.clear();
}

void CollisionDetector::reset(){
  foreachCollidable([](ICollidable * collidable){
    collidable->reset();
  });
}

void CollisionDetector::update(){
  foreachCollidable([](ICollidable * collidable){
    collidable->update();
  });
}

void CollisionDetector::addCollision(Collision * collision){
  _collisions.push_back(collision);
  collision->getObjectA().addCollision(collision);
  collision->getObjectB().addCollision(collision);
}

void CollisionDetector::foreachCollidable(std::function<void( ICollidable*)> f){
  for_each(_collidables.begin(), _collidables.end(), f);
}
void CollisionDetector::foreachPotentialCollision(std::function<void( ICollidable*,ICollidable*)> f){
  foreachCombination(f);
}

void CollisionDetector::foreachCombination(std::function<void (ICollidable * , ICollidable* )> f){
  for(int i =0; i < _collidables.size(); i++){
    for(int j = i+1; j < _collidables.size(); j++){
      ICollidable * a=_collidables.at(i);
      ICollidable * b=_collidables.at(j);
      f(a,b);
    }
  }
}

void CollisionDetector::foreachCollision(std::function<void (Collision* )>f){
  for_each(_collisions.begin(), _collisions.end(), f);
}

void CollisionDetector::foreachContact(std::function<void(Collision* ,Contact*)>f){
  foreachCollision([f](Collision * collision){
    function<void(Collision* ,Contact*)> f2 =f;
    collision->foreachContact([collision, f2](Contact* contact){
      f2(collision,contact);
    });
  });
}

bool CollisionDetector::addSimulationObject(ISimulationObject * object){
  ICollidable* collidable = dynamic_cast<ICollidable*>(object);
  if(!collidable)return false;
  if(!accepts(collidable))return false;
  _collidables.push_back(collidable);
  return true;
}

bool CollisionDetector::removeSimulationObject(ISimulationObject * object){
  ICollidable* collidable = dynamic_cast<ICollidable*>(object);
  if(!collidable)return false;
  auto it=  find(_collidables.begin(), _collidables.end(),collidable);
  if(it==_collidables.end())return false;
  _collidables.erase(it);
  return true;
}
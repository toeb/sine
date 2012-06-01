#include "CollisionDetector.h"

using namespace std;
using namespace IBDS;

CollisionDetector::CollisionDetector(){
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
  foreach([](Collidable * collidable){
    collidable->reset();
  });
}

void CollisionDetector::update(){
  foreach([](Collidable * collidable){
    collidable->update();
  });
}

void CollisionDetector::addCollision(Collision * collision){
  _collisions.push_back(collision);
  collision->getObjectA().addCollision(collision);
  collision->getObjectB().addCollision(collision);
}

void CollisionDetector::foreachCombination(std::function<void (Collidable * a, Collidable* b)> f){
  for(int i =0; i < objects().size(); i++){
    for(int j = 0; j < objects().size(); j++){
      if(i==j)continue;
      f(objects().at(i),objects().at(j));
    }
  }
}
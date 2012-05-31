#include "CollisionDetector.h"

using namespace std;
using namespace IBDS;

CollisionDetector::CollisionDetector(){
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
  collision->objectA.addCollision(collision);
  collision->objectB.addCollision(collision);
}

void CollisionDetector::foreachCombination(std::function<void (Collidable * a, Collidable* b)> f){
  for(int i =0; i < objects().size(); i++){
    for(int j = i+1; j < objects().size(); j++){
      f(objects().at(i),objects().at(j));
    }
  }
}
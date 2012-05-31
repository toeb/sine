#include "BoundingVolume.h"
using namespace IBDS;

BoundingVolume::BoundingVolume(const CoordinateSystem & parent):
_colliding(false),
  _coordinateSystem(parent),
_updated(false){

}

bool BoundingVolume::isUpToDate()const{
  return _updated;
}

void BoundingVolume::reset(){
  _updated =false;
  _colliding = false;
}
void BoundingVolume::update(){
  if(_updated)return;
  updateBoundingVolume();
  _updated = true;
}

bool BoundingVolume::isColliding()const{
  return _colliding;
}

void BoundingVolume::setColliding(bool flag){
  _colliding = flag;
}

const CoordinateSystem & BoundingVolume::getParentCoordinates()const{
  return _coordinateSystem;
}
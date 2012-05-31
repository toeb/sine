#include "BoundingSphere.h"


using namespace IBDS;


BoundingSphere::BoundingSphere(const AABB & aabb, const CoordinateSystem & coordinateSystem):BoundingVolume(coordinateSystem){
  _p_ocs = aabb.min+0.5*(aabb.max-aabb.min);
  setPosition(_p_ocs);
  setRadius((0.5*(aabb.max-aabb.min)).length());
}


Classification BoundingSphere::classify(Geometry & geometry)const{
  return geometry.classify(getPosition(),getRadius());
}

BoundingSphere * BoundingSphereFactory::create(Geometry & geometry, const AABB & aabb){
  BoundingSphere * sphere = new BoundingSphere(aabb, geometry);
  return sphere;
}

void BoundingSphere::updateBoundingVolume(){
  getParentCoordinates().fromObjectCoordinates(_p_ocs,position());
}

const Vector3D & BoundingSphere::getPositionOCS()const{
  return _p_ocs;
}
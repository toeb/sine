#include "BoundingSphere.h"


using namespace IBDS;


BoundingSphere::BoundingSphere(const AABB & aabb){
  position = aabb.min+0.5*(aabb.max-aabb.min);
  radius = (0.5*(aabb.max-aabb.min)).length();
}

Classification BoundingSphere::classify(Geometry & geometry)const{
  return geometry.classify(position,radius);
}

BoundingSphere * BoundingSphereFactory::create(Geometry & geometry, const AABB & aabb){
  BoundingSphere * sphere = new BoundingSphere(aabb);
  return sphere;
}
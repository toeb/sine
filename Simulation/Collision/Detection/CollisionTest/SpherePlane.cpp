#include "SpherePlane.h"


using namespace IBDS;

const TypeId SpherePlane::getTypeA()const{
  return Sphere::type;
}
const TypeId SpherePlane::getTypeB()const{
  return Plane::type;
}

bool SpherePlane::testCollision(const ICollidable & a, const ICollidable & b, Collision * collision)const{
  const Sphere & sphere = static_cast<const Sphere&>(a.getGeometry());
  
  return false;
}
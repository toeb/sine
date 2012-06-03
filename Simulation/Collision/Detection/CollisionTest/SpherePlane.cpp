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
  const Plane & plane = static_cast<const Plane & >(b.getGeometry());
  return testCollision(sphere,plane,collision);
}

bool SpherePlane::testCollision(const Sphere & sphere, const Plane & plane, Collision * col)const{
  Axis normalAxis;  
  plane.getNormalAxis(normalAxis);
  Interval sphereInterval;
  sphere.project(normalAxis,sphereInterval);
  
  if(sphereInterval.isAfter(0))return false;

  if(!col)return true;

  Contact * contact = new Contact();
  contact->normal = -normalAxis.n;
  contact->pA_wcs = normalAxis.p + sphereInterval.a * normalAxis.n;
  contact->pB_wcs = normalAxis.p;

  col->addContact(contact);
  
  return true;
}

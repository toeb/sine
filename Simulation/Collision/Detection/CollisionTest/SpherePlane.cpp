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
  normalAxis.n.normalize();
  Interval sphereInterval;
  sphere.project(normalAxis,sphereInterval);
  
  if(sphereInterval.isAfter(0))return false;

  if(!col)return true;

  Contact * contact = new Contact();
  contact->normal = -normalAxis.n;
  contact->pA_wcs = sphere.getPosition() + sphere.getRadius() * contact->normal;
  Vector2D position2D;
  plane.projectOnPlane(contact->pA_wcs,position2D);
  plane.getPositionFromUV(position2D,contact->pB_wcs);

  contact->penetrationDepth = (contact->pA_wcs-contact->pB_wcs).length();

  col->addContact(contact);
  
  return true;
}

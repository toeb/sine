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

bool SpherePlane::testCollision(const Sphere & sphere, const Plane & plane, Collision * collision)const{
  // axis that represents the plan
  Axis normalAxis;  
  plane.getNormalAxis(normalAxis);
  
  // interval of sphere projected on plane normal
  Interval sphereInterval;
  sphere.project(normalAxis,sphereInterval);
  
  // if the projection is on the positive side of the face then there is no collision
  if(sphereInterval.isAfter(0))return false;
  
  //if there is no collision object set parameters need not be computed
  if(!collision)return true;

  //create contact
  Contact * contact = new Contact();
  
  //contact normal from sphere to plane is the negative plane normal
  contact->normal = -normalAxis.n;

  //set point of collision of sphere
  contact->pA_wcs = sphere.getPosition() + sphere.getRadius() * contact->normal;
  
  //project the collisionPoint of sphere onto plane
  plane.projectOnPlane(contact->pA_wcs,contact->pB_wcs);

  contact->penetrationDepth = (contact->pA_wcs-contact->pB_wcs).length();

  //add contact to collision
  collision->addContact(contact);
    
  return true;
}

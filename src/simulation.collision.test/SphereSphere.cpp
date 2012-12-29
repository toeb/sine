#include "SphereSphere.h"

using namespace nspace;
using namespace std;

bool SphereSphere::testCollision(const Sphere & A, const Sphere & B, Collision * collision)const{
  Vector3D collisionNormal;

  //calculate the vector from A to B
  const Vector3D & pA = A.coordinates().position();
  const Vector3D & pB = B.coordinates().position();
  collisionNormal = pB-pA;
  //calculate the length
  Real length = collisionNormal.norm();

  // if lenth is near zero numerical instability might occur
  if(length==0){
    collisionNormal = Vector3D::UnitX();
  }

  // normalise the vector from A to B  to get the normal
  collisionNormal *= 1.0 /length;

  Real radiusA = A.radius();
  Real radiusB = B.radius();

  //add radii of the spheres
  Real combinedRadii = radiusA+radiusB;

  // calculate penetration depth
  Real penetrationDepth = combinedRadii-length;

  //positive penetration means the objects are inside each other, negative--> no collision
  if(penetrationDepth<0)return false;

  //if there is no collision set then no contact parameters have to be computed
  if(!collision)return true;

  Contact * contact = ContactPool::instance().createContact();//new Contact();

  //set position of collision at body a and b
  //contact->pA_wcs = pA;
  //contact->pB_wcs = pB;

  //set penetration depth and collision normal
  contact->penetrationDepth = penetrationDepth;
  contact->normal = collisionNormal;

  //set point of collision A:  collision->pA_wcs = pA + n * radiusA
  contact->pA_wcs = contact->normal * radiusA;
  contact->pA_wcs += pA ;

  //set point of collision B:  collision->pB_wcs = pB - n * radiusB
  contact->pB_wcs = contact->normal * (-radiusA);
  contact->pB_wcs += pB ;

  //add contact point to collision
  collision->addContact(contact);

  return true;
}

bool SphereSphere::testCollision(const ISimulationObject & objA, const ISimulationObject & objB, Collision * collision)const{
  const Sphere & A = static_cast<const Sphere&>(objA);
  const Sphere & B = static_cast<const Sphere&>(objB);
  return testCollision(A,B,collision);
}
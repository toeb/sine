#include "SphereSphere.h"

using namespace IBDS;
using namespace std;
  
const TypeId SphereSphere::getTypeA()const{
  return Sphere::type;
}
const TypeId SphereSphere::getTypeB()const{
  return Sphere::type;
}

bool SphereSphere::testCollision(const Sphere & A, const Sphere & B, Collision * collision)const{
  Vector3D collisionNormal;

  //calculate the vector from A to B
  const Vector3D & pA = A.coordinates().position();
  const Vector3D & pB = B.coordinates().position();
  Vector3D::subtract(pB,  pA,collisionNormal);
  
  //calculate the length
  Real length = collisionNormal.length();

  // if lenth is near zero numerical instability might occur
  if(length==0){  
    collisionNormal.set(1,0,0);
  }

  // normalise the vector from A to B  to get the normal
  Vector3D::multiplyScalar(1.0/length,collisionNormal,collisionNormal);

  Real radiusA = A.getRadius();
  Real radiusB = B.getRadius();

  //add radii of the spheres
  Real combinedRadii = radiusA+radiusB;
  
  // calculate penetration depth 
  Real penetrationDepth = combinedRadii-length;
  
  //positive penetration means the objects are inside each other, negative--> no collision
  if(penetrationDepth<0)return false;

  //if there is no collision set then no contact parameters have to be computed
  if(!collision)return true;

  Contact * contact = new Contact();

  //set position of collision at body a and b
  //contact->pA_wcs = pA;
  //contact->pB_wcs = pB;

  //set penetration depth and collision normal
  contact->penetrationDepth = penetrationDepth;
  contact->normal = collisionNormal;

  //set point of collision A:  collision->pA_wcs = pA + n * radiusA 
  Vector3D::multiplyScalar(radiusA,contact->normal, contact->pA_wcs);
  Vector3D::add(contact->pA_wcs,pA,contact->pA_wcs);

  //set point of collision B:  collision->pB_wcs = pB - n * radiusB
  Vector3D::multiplyScalar(-radiusB,contact->normal,contact->pB_wcs);
  Vector3D::add(contact->pB_wcs,pB,contact->pB_wcs);
  
  //add contact point to collision
  collision->addContact(contact);

  return true;
}

bool SphereSphere::testCollision(const ISimulationObject & objA, const ISimulationObject & objB, Collision * collision)const{
  
  const Sphere & A = static_cast<const Sphere&>(objA);
  const Sphere & B = static_cast<const Sphere&>(objB);
  return testCollision(A,B,collision);  
}

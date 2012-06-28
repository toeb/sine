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
  const Vector3D & pA = A.getPosition();
  const Vector3D & pB = B.getPosition();
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


  //set position of collision at body a and b
  //contact->pA_wcs = pA;
  //contact->pB_wcs = pB;
  Vector3D contact_pA_wcs, contact_pB_wcs;

  //set point of collision A:  collision->pA_wcs = pA + n * radiusA 
  Vector3D::multiplyScalar(radiusA,collisionNormal, contact_pA_wcs);
  Vector3D::add(contact_pA_wcs,pA,contact_pA_wcs);

  //set point of collision B:  collision->pB_wcs = pB - n * radiusB
  Vector3D::multiplyScalar(-radiusB,collisionNormal,contact_pB_wcs);
  Vector3D::add(contact_pB_wcs,pB,contact_pB_wcs);
  
  //add contact point to collision
  collision->addContact(new Contact(*collision->getObjectA().getDynamicBody(), *collision->getObjectB().getDynamicBody(),contact_pA_wcs, contact_pB_wcs, collisionNormal, penetrationDepth));

  return true;
}

bool SphereSphere::testCollision(const ICollidable & objA, const ICollidable & objB, Collision * collision)const{
  const Sphere & A = static_cast<const Sphere &>(objA.getGeometry());
  const Sphere & B = static_cast<const Sphere &>(objB.getGeometry());
  return testCollision(A,B,collision);  
}

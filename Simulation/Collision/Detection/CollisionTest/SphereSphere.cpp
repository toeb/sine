#include "SphereSphere.h"
#include <Math/MathDefs.h>
using namespace IBDS;
using namespace std;



  
const TypeId SphereSphere::getTypeA()const{
  return Sphere::type;
}
const TypeId SphereSphere::getTypeB()const{
  return Sphere::type;
}



bool SphereSphere::testCollision(const Sphere & A, const Sphere & B, Collision * collision)const{
  //calculate the vector from A to B
  const Vector3D & pA = A.getPosition();
  const Vector3D & pB = B.getPosition();

  Vector3D collisionNormal;

  Vector3D::subtract(pB,  pA,collisionNormal);
  
  //calculate the length
  Real length = collisionNormal.length();

  // if lenth is near zero numerical instability might occur
  if(length==0){  
    collisionNormal.set(1,0,0);
  }

  // normalise the vector from A to B 
  Vector3D::multiplyScalar(1/length,collisionNormal,collisionNormal);

  Real radiusA = A.getRadius();
  Real radiusB = B.getRadius();
  //add radii of the spheres
  Real combinedRadii = radiusA+radiusB;
  
  // calculate penetration depth 
  Real penetrationDepth = combinedRadii-length;
  
  //positive penetration means the objects are inside each other
  if(penetrationDepth<0)return false;
  //if there is no collision set then no contact parameters have to be computed
  if(!collision)return true;

  Contact * contact = new Contact();
  contact->penetrationDepth = penetrationDepth;
  contact->normal = collisionNormal;
  //set point of collision A:  pA = positionA + n * radiusA 
  Vector3D::multiplyScalar(radiusA,contact->normal, contact->pA_wcs);
  Vector3D::add(contact->pA_wcs,pA,contact->pA_wcs);

  //set point of collision B:  pB = positionB + n * radiusB
  Vector3D::multiplyScalar(-radiusB,contact->normal,contact->pB_wcs);
  Vector3D::add(contact->pB_wcs,pB,contact->pB_wcs);
  
  collision->addContact(contact);
}

bool SphereSphere::testCollision(const ICollidable & objA, const ICollidable & objB, Collision * collision)const{
  const Sphere & A = static_cast<const Sphere &>(objA.getGeometry());
  const Sphere & B = static_cast<const Sphere &>(objB.getGeometry());
  return testCollision(A,B,collision);  
}

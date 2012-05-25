#include "SphereSphere.h"

using namespace IBDS;
using namespace std;


bool SphereSphere::testCollision(Collision & collision)const{
  //calculate the vector from A to B
  const Vector3D & pA = _A->getPosition();
  const Vector3D & pB = _B->getPosition();

  Vector3D::subtract(pB,  pA,collision.normal);
  
  //calculate the length
  Real length = collision.normal.length();

  // if lenth is near zero numerical instability might occur
  if(abs(length)<EPSILON){
    cout <<"Sphere Sphere test: spheres are at the same position"<<endl;
  }

  // normalise the vector from A to B 
  Vector3D::multiplyScalar(1/length,collision.normal,collision.normal);

  Real radiusA = _A->getRadius();
  Real radiusB = _B->getRadius();
  //add radii of the spheres
  Real combinedRadii = radiusA+radiusB;
  
  // calculate penetration depth 
  collision.penetrationDepth = combinedRadii-length;
  
  //positive penetration means the objects are inside each other
  if(collision.penetrationDepth<0)return false;
  
  //set objects  
  collision.objectA = _A;
  collision.objectB=  _B;
  
  //set point of collision A:  pA = positionA + n * radiusA 
  Vector3D::multiplyScalar(radiusA,collision.normal, collision.pA_wcs);
  Vector3D::add(collision.pA_wcs,pA,collision.pA_wcs);

  //set point of collision B:  pB = positionB + n * radiusB
  Vector3D::multiplyScalar(-radiusB,collision.normal, collision.pB_wcs);
  Vector3D::add(collision.pB_wcs,pB,collision.pB_wcs);

}
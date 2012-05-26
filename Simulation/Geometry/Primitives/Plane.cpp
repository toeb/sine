#include "Plane.h"

using namespace std;
using namespace IBDS;

Plane::Plane( const Vector2D & dimension):
 _dimension(dimension){

}
bool Plane::isInside(const Vector3D & p_wcs){
  Vector3D p_ocs ;
  toObjectCoordinates(p_wcs,p_ocs);
  if(abs(p_ocs[2]) > EPSILON)return false;
  if(p_ocs[0]*p_ocs[0]+p_ocs[1]*p_ocs[1] > _dimension.length2())return false;
  return true;
}

Real Plane::calculateBoundingSphereRadius()const{
  return _dimension.length2();
}

void Plane::setDimension(const Vector3D & dim){
  _dimension=dim;
}
void Plane::setDimension(Real x,Real y){
  _dimension[0]=x;
  _dimension[1]=y;

}
const Vector2D & Plane::getDimension()const{
  return _dimension;
}
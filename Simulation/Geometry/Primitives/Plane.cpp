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
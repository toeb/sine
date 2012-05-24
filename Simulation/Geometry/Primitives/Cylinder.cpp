#include "Cylinder.h"

using namespace IBDS;
using namespace std;

Cylinder::Cylinder(Real radius, Real height):_radius(radius),_height(height){

}

bool Cylinder::isInside(const Vector3D & p_wcs)const{
  Vector3D p_ocs;
  toObjectCoordinates(p_wcs,p_ocs);
  Real h = _height /2;
  if(p_ocs[2] > h)return false;
  if(p_ocs[2] < -h)return false;

  if(_radius*_radius < p_ocs[0]*p_ocs[0]+p_ocs[1]*p_ocs[1]){
    return false;
  }
  return true;
}

Real Cylinder::calculateBoundingSphereRadius()const{
  //the center is in the middle of x,y,z values
  return sqrt(_radius*_radius+(_height*_height/4)); 
}
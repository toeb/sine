#include "Sphere.h"

using namespace std;
using namespace IBDS;

Sphere::Sphere(Real radius){
  _radius = radius;
}
bool Sphere::isInside(const Vector3D & p_wcs)const{
  Vector3D r_p_wcs;
  Vector3D::subtract(p_wcs,getPosition(),r_p_wcs);
  Real lengthSquared = r_p_wcs.length2();
  if(_radius*_radius < lengthSquared)return true;
  else return false;
}

Real Sphere::calculateBoundingSphereRadius()const{
  return _radius;
}

Real Sphere::getRadius()const{
  return _radius;
}
void Sphere::setRadius(Real radius){
  if(radius < 0){
    cout<<"Sphere radius was smaller than zero";
    return;
  }
  _radius = radius;
  onRadiusChanged();
}
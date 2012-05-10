#include "Body.h"
using namespace IBDS;


void Body::previewPosition(Real h, Vector3D & s_next_wcs)const{
  const Vector3D & s_wcs = getPosition();
  const Vector3D & v_wcs = getVelocity();
  const Vector3D & a_wcs = getAcceleration();
  Vector3D s_preview = s_wcs + h*v_wcs+ 0.5*h*h*a_wcs;
  s_next_wcs.assign(s_preview);
}


void Body::calculateAcceleration(){
  Real m = getMass();
  if(m==0){
    _acceleration =  Vector3D::Zero();
    return;
  }
  const Vector3D & f = getForce();
  _acceleration = (1/m)*f;  
}
const Vector3D & Body::getAcceleration()const {
  return _acceleration;
}
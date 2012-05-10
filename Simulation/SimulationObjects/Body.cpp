#include "Body.h"
using namespace IBDS;


const Vector3D & Body::previewPosition(Real h)const{
  const Vector3D & s_wcs = getPosition();
  const Vector3D & v_wcs = getVelocity();
  const Vector3D & a_wcs = getAcceleration();
  Vector3D s_preview = s_wcs + h*v_wcs+ 0.5*h*h*a_wcs;
  return s_preview.copy();
}



const Vector3D & Body::getAcceleration()const {
  Real m = getMass();
  if(m==0)return Vector3D::Zero();
  const Vector3D & f = getForce();
  return ((1/m)*f).copy();
}
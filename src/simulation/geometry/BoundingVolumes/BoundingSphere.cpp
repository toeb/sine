#include "BoundingSphere.h"


using namespace IBDS;


BoundingSphere::BoundingSphere(const Vector3D & min, const Vector3D & max, const CoordinateSystem & coordinateSystem):BoundingVolume(coordinateSystem){
  _p_pcs = min+0.5*(max-min);
  //coordinates().position()=_p_pcs;
  setRadius((0.5*(max-min)).length());
}


BoundingSphere * BoundingSphereFactory::create(const Vector3D & min, const Vector3D & max,const CoordinateSystem & parentObject){
  BoundingSphere * sphere = new BoundingSphere(min,max,parentObject);
  return sphere;
}

void BoundingSphere::updateBoundingVolume(){
  parentCoordinates().fromObjectCoordinates(_p_pcs,coordinates().position());
}

const Vector3D & BoundingSphere::getPositionPCS()const{
  return _p_pcs;
}
void BoundingSphere::projectPCS(const Axis & axis, Interval & result)const{
  Real val = axis.projectOnAxis(_p_pcs);
  result.a = val-radius();
  result.b = val+radius();
}
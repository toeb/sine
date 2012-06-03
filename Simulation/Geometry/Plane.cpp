#include "Plane.h"
#include <Simulation/Geometry/Axis.h>

using namespace IBDS;

const TypeId Plane::type="Plane";
const TypeId Plane::getType()const{
  return type;
}

 void  Plane::getNormal(Vector3D & n)const{
  Matrix3x3 RT;
  getOrientation().getMatrix3x3T(RT);
  n.assign(RT.v[1]);
}
 void  Plane::getUAxis(Axis & a)const{
  Matrix3x3 RT;
  getOrientation().getMatrix3x3T(RT);
  a.n.assign(RT.v[0]);
  a.p.assign(getPosition());
}
 void  Plane::getVAxis(Axis & b)const{
  Matrix3x3 RT;
  getOrientation().getMatrix3x3T(RT);
  b.n.assign(RT.v[2]);
  b.p.assign(getPosition());
}
Vector3D Plane::getPositionFromUV(const Vector2D & uv)const{
  Vector3D p;
  getPositionFromUV(uv,p);
  return p;
}
 void  Plane::getPositionFromUV(const Vector2D & uv, Vector3D & p)const{
  Axis u,v;
  getUAxis(u);
  getVAxis(v);  
  
  p = getPosition()+u.n*uv[0]+v.n*uv[1];
}
 Vector3D Plane::getNormal()const{
  Vector3D result;
  getNormal(result);
  return result;
}

 bool Plane::isInFront(const Vector3D & p)const{
  Real val = projectOnNormal(p);
  if(val > 0)return true;
  else return false;
}


 void Plane::projectOnPlane(const Vector3D & p, Vector2D & result)const{
  Axis uAxis, vAxis;
  getUAxis(uAxis);
  getVAxis(vAxis);

  result[0] = uAxis.projectOnAxis(p);
  result[1] = vAxis.projectOnAxis(p);

}
 Real Plane::projectOnNormal(const Vector3D & p)const{
  Axis axis;
  getNormal(axis.n);
  axis.p = getPosition();
  Real val = axis.projectOnAxis(p);
  return val;
}

 void Plane::getNormalAxis(Axis & nAxis)const{
  nAxis.n = getNormal();
  nAxis.p = getPosition();
}
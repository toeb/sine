#include "Plane.h"
#include <simulation.geometry/Axis.h>

using namespace nspace;

void  Plane::getNormal(Vector3D & n)const{
  Matrix3x3 RT;
  coordinates().orientation().toTransposedRotationMatrix(RT);
  n = RT.row(1);
  n.normalize();
}
void  Plane::getUAxis(Axis & a)const{
  Matrix3x3 RT;
  coordinates().orientation().toTransposedRotationMatrix(RT);
  a.n = RT.row(0);
  a.p =coordinates().position();
}
void  Plane::getVAxis(Axis & b)const{
  Matrix3x3 RT;
  coordinates().orientation().toTransposedRotationMatrix(RT);
  b.n = RT.row(2);
  b.p=(coordinates().position());
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

  p = coordinates().position()+u.n*uv(0)+v.n*uv(1);
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

  result(0) = uAxis.projectOnAxis(p);
  result(1) = vAxis.projectOnAxis(p);
}

void Plane::projectOnPlane(const Vector3D & p, Vector3D & p_plane)const{
  Vector2D uv;
  projectOnPlane(p,uv);
  getPositionFromUV(uv,p_plane);
}

Real Plane::projectOnNormal(const Vector3D & p)const{
  Axis axis;
  getNormal(axis.n);
  axis.p = coordinates().position();
  Real val = axis.projectOnAxis(p);
  return val;
}

void Plane::getNormalAxis(Axis & nAxis)const{
  nAxis.n = getNormal();
  nAxis.p = coordinates().position();
}
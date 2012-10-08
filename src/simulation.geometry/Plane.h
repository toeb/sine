#pragma once
#include <simulation.geometry/Geometry.h>
#include <math/core.h>
#include <simulation.geometry/Axis.h>
namespace nspace{
class Plane:public Geometry{
  TYPED_OBJECT(Plane);
public:

  void getNormal(Vector3D & n)const;
  void getNormalAxis(Axis & nAxis)const;
  void getUAxis(Axis & a)const;
  void getVAxis(Axis & b)const;
  void getPositionFromUV(const Vector2D & uv, Vector3D & p)const;
  Vector3D getPositionFromUV(const Vector2D & uv)const;
  Vector3D getNormal()const;
  bool isInFront(const Vector3D & p)const;
  void projectOnPlane(const Vector3D & p, Vector2D & result)const;
  void projectOnPlane(const Vector3D & p, Vector3D & p_plane)const;
  Real projectOnNormal(const Vector3D & p)const;
};
}

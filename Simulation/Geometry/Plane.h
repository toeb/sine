#pragma once
#include <Simulation/Geometry/CoordinateSystem.h>
#include <Math/Vector2D.h>
namespace IBDS{
class Plane:public CoordinateSystem{
  
public:
  static const TypeId type;
  const TypeId getType()const;
  inline void getNormal(Vector3D & n)const;
  inline void getAxisA(Vector3D & a)const;
  inline void getAxisB(Vector3D & b)const;
  inline void getPositionFromUV(const Vector2D & uv, Vector3D & p)const; 
  inline Vector3D getNormal()const;

};
}
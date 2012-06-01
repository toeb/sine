#include "Plane.h"

using namespace IBDS;

const TypeId Plane::type="Plane";
const TypeId Plane::getType()const{
  return type;
}

inline void  Plane::getNormal(Vector3D & n)const{
  Matrix3x3 RT;
  getOrientation().getMatrix3x3T(RT);
  n.assign(RT.v[1]);
}
inline void  Plane::getAxisA(Vector3D & a)const{
  Matrix3x3 RT;
  getOrientation().getMatrix3x3T(RT);
  a.assign(RT.v[0]);

}
inline void  Plane::getAxisB(Vector3D & b)const{
  Matrix3x3 RT;
  getOrientation().getMatrix3x3T(RT);
  b.assign(RT.v[2]);

}
inline void  Plane::getPositionFromUV(const Vector2D & uv, Vector3D & p)const{
  Vector3D a,b;
  getAxisA(a);
  getAxisB(b);  
  
  p = getPosition()+a*uv[0]+b*uv[1];
}
inline Vector3D Plane::getNormal()const{
  Vector3D result;
  getNormal(result);
  return result;
}


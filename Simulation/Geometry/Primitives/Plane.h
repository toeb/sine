#pragma once
#include <Simulation/Geometry/GeometricObject.h>
#include <Math/Vector2D.h>
namespace IBDS{
class Plane : public virtual GeometricObject{
private:
  Vector2D _dimension;
public:
  Plane(const Vector2D & dimension);
  bool isInside(const Vector3D & p_wcs);
  Real calculateBoundingSphereRadius()const;
};
}
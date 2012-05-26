#pragma once
#include <Simulation/Geometry/GeometricObject.h>
#include <Math/Vector2D.h>
namespace IBDS{
class Plane : public virtual GeometricObject{
private:
  Vector2D _dimension;
public:
  void setDimension(const Vector3D & dim);
  void setDimension(Real x,Real y);
  const Vector2D & getDimension()const;


  Plane(const Vector2D & dimension);
  bool isInside(const Vector3D & p_wcs);
  Real calculateBoundingSphereRadius()const;
};
}
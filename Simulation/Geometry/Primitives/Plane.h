#pragma once
#include <Simulation/Geometry/Polygon/Polygon.h>
#include <Math/Vector2D.h>
namespace IBDS{
class Plane : public virtual Polygon{
private:
  Vector2D _dimension;
public:
  Plane(const Vector2D & dimension);

  void setDimension(const Vector2D & dim);
  void setDimension(Real x,Real y);
  const Vector2D & getDimension()const;

  void getNormal(Vector3D & normal)const;

protected:
  void createGeometry();
};
}
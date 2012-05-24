#pragma once
#include <Simulation/Geometry/GeometricObject.h>
namespace IBDS{
class Sphere : public virtual GeometricObject{
private:
  Real _radius;
public:
  Sphere(Real radius=1.0);
  bool isInside(const Vector3D & p_wcs);
  Real calculateBoundingSphereRadius()const;
};
}
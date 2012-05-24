#pragma once
#include <Simulation/Geometry/GeometricObject.h>

namespace IBDS{
class Cylinder:public virtual GeometricObject{
private:
  Real _radius;
  Real _height;
public:
  Cylinder(Real radius = 1.0, Real height=2.0);
  bool isInside(const Vector3D & p_wcs)const;
  Real calculateBoundingSphereRadius()const;
};
}
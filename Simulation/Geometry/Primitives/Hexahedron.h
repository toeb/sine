#pragma once

#include <Simulation/Geometry/GeometricObject.h>

namespace IBDS{
class Hexahedron : public virtual GeometricObject{
private:
  Real _xExtent;
  Real _yExtent;
  Real _zExtent;
public:
  Hexahedron(Real x= 0,Real y=0,Real z=0);
  bool isInside(const Vector3D & p_wcs)const;
  Real calculateBoundingSphereRadius()const;
};
}
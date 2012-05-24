#pragma once

#include <Simulation/Geometry/CoordinateSystem.h>

namespace IBDS{
class GeometricObject : public virtual CoordinateSystem{
public:
  virtual bool isInside(const Vector3D & p_wcs)const=0;
  virtual Real calculateBoundingSphereRadius()const=0;
};
}
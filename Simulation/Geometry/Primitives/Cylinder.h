#pragma once
#include <Simulation/Geometry/Geometry.h>

namespace IBDS{
class Cylinder:public virtual Geometry{
private:
  Real _radius;
  Real _height;
public:
  Cylinder(Real radius = 1.0, Real height=2.0);
  Real calculateBoundingSphereRadius()const;
};
}
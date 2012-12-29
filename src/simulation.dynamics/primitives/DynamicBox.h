#pragma once

#include <math/core.h>
#include <simulation.geometry/primitives/Hexahedron.h>
#include <simulation.dynamics/primitives/DynamicGeometry.h>
namespace nspace{
  class DynamicBox: public DynamicGeometry<Hexahedron>
  {
    Hexahedron _hexahedron;
  public:
    DynamicBox(Real m=1, Real x=1, Real y=1, Real z=1);
    static Matrix3x3 calculateInertia(Real m, Real x,Real y, Real z);
  };
}

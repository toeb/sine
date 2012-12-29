#pragma once

#include <simulation.geometry/primitives/Sphere.h>
#include <simulation.dynamics/primitives/DynamicGeometry.h>

namespace nspace{
  class DynamicSphere: public DynamicGeometry<Sphere>
  {
  public:

    /**
    *  Creates a sphere with given mass and radius.
    * \param m mass
    * \param r radius
    */
    DynamicSphere(Real m=1, Real r=1);
    static Matrix3x3 calculateInertia(Real m, Real r);
  };
}
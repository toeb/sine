#pragma once


#include <Math/Matrix3x3.h>
#include <Simulation/Geometry/Primitives/Hexahedron.h>
#include <Simulation/Dynamics/BodyPrimitives/DynamicGeometry.h>
namespace IBDS{
class DynamicBox: public DynamicGeometry<Hexahedron>
{
  Hexahedron _hexahedron;
public:
  DynamicBox(Real m=1, Real x=1, Real y=1, Real z=1);
  static Matrix3x3 calculateInertia(Real m, Real x,Real y, Real z);
};
}

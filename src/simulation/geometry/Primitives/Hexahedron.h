#pragma once

#include <simulation/geometry/polygon/Polygon.h>

namespace nspace{
class Hexahedron : public Polygon{
private:
  Real _xExtent;
  Real _yExtent;
  Real _zExtent;
public:
  Hexahedron(Real x= 0,Real y=0,Real z=0);
  Real getXExtent()const;
  Real getYExtent()const;
  Real getZExtent()const;
protected:
  void createGeometry();
};
}
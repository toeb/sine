#pragma once
#include <Visualization/IRenderer.h>
#include <Simulation/Geometry/Plane.h>

namespace IBDS{


class PlaneRenderer :public IRenderer{
private:
  Plane & _plane;
  Real _extent;
public:
  Real & extent(){return _extent;}
  PlaneRenderer( Plane & plane, Real extent=100);
  void render();
};
}
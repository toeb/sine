#pragma once
#include <visualization/Renderer.h>
#include <simulation.geometry/Plane.h>

namespace nspace{


class PlaneRenderer :public Renderer{
private:
  Plane & _plane;
  Real _extent;
public:
  Real & extent(){return _extent;}
  PlaneRenderer( Plane & plane, Real extent=100);
  void render();
};
}
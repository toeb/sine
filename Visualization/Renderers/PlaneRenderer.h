#pragma once
#include <Visualization/IRenderer.h>
#include <Simulation/Geometry/Primitives/Plane.h>

namespace IBDS{


class PlaneRenderer :public IRenderer{
private:
  Plane & _plane;
public:
  PlaneRenderer( Plane & plane);
  void render();
};
}
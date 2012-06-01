#pragma once
#include <Visualization/IRenderer.h>
#include <Simulation/Geometry/Primitives/Rectangle.h>

namespace IBDS{


class RectangleRenderer :public IRenderer{
private:
  Rectangle & _plane;
public:
  RectangleRenderer( Rectangle & plane);
  void render();
};
}
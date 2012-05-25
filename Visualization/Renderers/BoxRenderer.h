#pragma once
#include <Visualization/IRenderer.h>

#include <Simulation/Geometry/Primitives/Hexahedron.h>
#include <Visualization/Renderers/TextRenderer.h>

namespace IBDS{
  
class BoxRenderer : public IRenderer{
private:  
  TextRenderer * _textRenderer;
  const Hexahedron & _box;
  const Vector3D & _p;
  Vector3D _textPosition;
  Vector3D boxExtent;
public:
  bool initializeObject();
  BoxRenderer(const Hexahedron & box);
  void render();
};
}
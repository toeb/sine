#pragma once
#include <visualization/core/IRenderer.h>

#include <simulation/geometry/primitives/Hexahedron.h>
#include <visualization/glrenderers/general/TextRenderer.h>

namespace nspace{
  
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
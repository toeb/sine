#pragma once
#include <Visualization/IRenderer.h>
#include <Simulation/SimulationObjects/Box.h>
#include <Visualization/Renderers/TextRenderer.h>

namespace IBDS{
  
class BoxRenderer : public IRenderer{
private:  
  TextRenderer * _textRenderer;
  const Box & _box;
  const Matrix3x3  & _RT;
  const Vector3D & _p;
  Vector3D boxExtent;
public:
  bool initialize();
  BoxRenderer(const Box & box);
  void render();
};
}
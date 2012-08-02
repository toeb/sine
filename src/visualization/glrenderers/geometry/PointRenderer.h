#pragma once
#include <visualization/core/IRenderer.h>
#include <math/definitions.h>
namespace nspace{
class PointRenderer :public IRenderer{
private:
  const Vector3D & _pointCoordinates;
public:
  PointRenderer(const Vector3D & pointCoordinates);
  void render();
};
}
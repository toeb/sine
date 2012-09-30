#pragma once
#include <visualization/Renderer.h>
#include <math/core.h>
namespace nspace{
class PointRenderer :public virtual Renderer{
private:
  const Vector3D & _pointCoordinates;
public:
  PointRenderer(const Vector3D & pointCoordinates);
  void render();
};
}
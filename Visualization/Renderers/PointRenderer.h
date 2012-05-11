#pragma once
#include <Visualization/IRenderer.h>
#include <Math/Vector3D.h>
namespace IBDS{
class PointRenderer :public IRenderer{
private:
  const Vector3D & _pointCoordinates;
public:
  PointRenderer(const Vector3D & pointCoordinates);
  void render();
};
}
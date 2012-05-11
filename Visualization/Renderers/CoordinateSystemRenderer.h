#pragma once
#include <Visualization/IRenderer.h>
#include <Visualization/MiniGL.h>
namespace IBDS{
class CoordinateSystemRenderer:public IRenderer{
private:
  const Vector3D & _origin;
  const Quaternion & _orientation;
  Matrix3x3 _orientationMatrix;
public:
  CoordinateSystemRenderer();
  CoordinateSystemRenderer(const Vector3D& origin, const Quaternion & orientation);
  void render();
};
}

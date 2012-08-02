#pragma once

#include <Visualization/IRenderer.h>
#include <Simulation/Geometry/Primitives/Sphere.h>

namespace IBDS{
class SphereRenderer : public virtual IRenderer{
private:
  Sphere & _sphere;
public:
  SphereRenderer(Sphere & sphere):_sphere(sphere){}
  void render();
};
}
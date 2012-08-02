#pragma once

#include <visualization/core/IRenderer.h>
#include <simulation/geometry/primitives/sphere.h>

namespace nspace{
class SphereRenderer : public virtual IRenderer{
private:
  Sphere & _sphere;
public:
  SphereRenderer(Sphere & sphere):_sphere(sphere){}
  void render();
};
}
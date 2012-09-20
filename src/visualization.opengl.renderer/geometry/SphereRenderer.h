#pragma once

#include <visualization/IRenderer.h>
#include <simulation.geometry/primitives/Sphere.h>

namespace nspace{
class SphereRenderer : public virtual IRenderer{
private:
  Sphere & _sphere;
public:
  SphereRenderer(Sphere & sphere):_sphere(sphere){}
  void render();
};
}

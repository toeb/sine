#pragma once

#include <visualization/Renderer.h>
#include <simulation.geometry/primitives/Sphere.h>

namespace nspace{
class SphereRenderer : public virtual Renderer{
private:
  Sphere & _sphere;
public:
  SphereRenderer(Sphere & sphere):_sphere(sphere){}
  void render();
};
}

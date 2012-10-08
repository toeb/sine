#pragma once
#include <core/Set.h>

#include <visualization/Renderer.h>
#include <simulation.geometry/primitives/Sphere.h>

namespace nspace{
class SphereRenderer : public virtual Renderer, public virtual Set<Sphere*>{

public:
  void render();
};//SphereMesh
}

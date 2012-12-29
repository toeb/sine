#pragma once
#include <core.collection.h>

#include <visualization/Renderer.h>
#include <simulation.geometry/primitives/Sphere.h>

namespace nspace{
class SphereRenderer : public virtual Renderer, public virtual Set<Sphere*>{

public:
  void render();
};//SphereMesh
}

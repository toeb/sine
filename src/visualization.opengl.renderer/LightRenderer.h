#pragma once
#include <visualization/Renderer.h>
#include <core/Set.h>
#include <visualization/Light.h>
namespace nspace{

class LightRenderer : public virtual Renderer, public virtual Set<Light*>{
  TYPED_OBJECT(LightRenderer);
public:
  void doLights();
  void render();
  void onBeforeRendering();
};
};
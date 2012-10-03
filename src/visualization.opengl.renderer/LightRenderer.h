#pragma once
#include <visualization/Renderer.h>
namespace nspace{
  
class LightRenderer : public Renderer{
public:
  void doLights();
  void render();
  void onBeforeRendering();
};
};
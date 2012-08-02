#pragma once
#include <visualization/core/IRenderer.h>
namespace nspace{
  
class LightRenderer : public IRenderer{
public:
  void doLights();
  void render();
  void onBeforeRendering();
};
};
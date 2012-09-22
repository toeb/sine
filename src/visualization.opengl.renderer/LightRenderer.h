#pragma once
#include <visualization/IRenderer.h>
namespace nspace{
  
class LightRenderer : public IRenderer{
public:
  void doLights();
  void render();
  void onBeforeRendering();
};
};
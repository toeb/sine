#pragma once
#include <vis/IRenderer.h>
namespace mbslib{
  
class LightRenderer : public IRenderer{
public:
  void doLights();
  void render();
  void onBeforeRendering();
};
};
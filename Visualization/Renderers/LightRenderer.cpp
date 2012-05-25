#include "LightRenderer.h"
#include <Visualization/MiniGL.h>
using namespace IBDS;

 void LightRenderer::onBeforeRenderering(){  
  MiniGL::initLights();	
  
}
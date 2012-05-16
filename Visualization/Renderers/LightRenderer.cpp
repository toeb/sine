#include "LightRenderer.h"
#include <Visualization/MiniGL.h>
using namespace IBDS;

 bool LightRenderer::initializeObject(){  
  MiniGL::initLights();	
  return true;
}
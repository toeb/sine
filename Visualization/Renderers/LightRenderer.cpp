#include "LightRenderer.h"
#include <Visualization/MiniGL.h>
using namespace IBDS;

 bool LightRenderer::initialize(){  
  MiniGL::initLights();	
  return true;
}
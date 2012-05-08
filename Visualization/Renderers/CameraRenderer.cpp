#include "CameraRenderer.h"
#include <Visualization/MiniGL.h>
using namespace IBDS;

bool CameraRenderer::initialize(){
      MiniGL::setViewport (40.0f, 1.0f, 100.0f, Vector3D (15.0, 1.0, 20.0), Vector3D (5.0, -4, 0.0));
      return true;
}
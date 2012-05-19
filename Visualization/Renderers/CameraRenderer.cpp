
#ifdef WIN32
#include "windows.h"
#endif
#include "GL/gl.h"
#include "GL/glu.h"

#include "CameraRenderer.h"
#include <Visualization/MiniGL.h>


using namespace IBDS;

void CameraRenderer::setInputHandler(InputHandler * handler){
  _input = handler;
}
void CameraRenderer::onBeforeRenderering(){
      MiniGL::setViewport (40.0f, 1.0f, 100.0f, Vector3D (15.0, 1.0, 20.0), Vector3D (5.0, -4, 0.0));
}
void CameraRenderer::render(){
  MiniGL::drawVector(Vector3D(0,0,-100),Vector3D(0,0,100),1,MiniGL::black);
  MiniGL::drawVector(Vector3D(0,-100,0),Vector3D(0,100,0),1,MiniGL::black);
  MiniGL::drawVector(Vector3D(-100,0,0),Vector3D(100,0,0),1,MiniGL::black);
}


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
bool CameraRenderer::initializeObject(){
      MiniGL::setViewport (40.0f, 1.0f, 100.0f, Vector3D (15.0, 1.0, 20.0), Vector3D (5.0, -4, 0.0));
      return true;
}
void CameraRenderer::render(){
  setVelocity(Vector3D(0,0,0));
 /*if(_input){
    if(_input->isKeyDown(Keys::KEY_B))setVelocity(Vector3D(1,1,0));
    if(_input->isKeyDown(Keys::KEY_V))setVelocity(Vector3D(-1,-1,0));
    
  }
  const Vector3D & p = getPosition();
  //glTranslatef(p[0],p[1],p[2]);
  */
}

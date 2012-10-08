
#include "LightRenderer.h"
#include <visualization.opengl/opengl.h>
#include <visualization.opengl/Utility.h>
#include <visualization.opengl/MiniGL.h>
using namespace nspace;

void LightRenderer::doLights(){
  glDisableLights();
  for(uint i=0; i < 8 && i < size();i++){
    nspace::glLight(i,*at(i));
  }
  glEnable(GL_LIGHTING);
}
void LightRenderer::render(){
  foreachElement([](Light * light){
    glPushMatrix();
    glTransformation(light->Coordinates());    
    //glTranslate(light->Coordinates().position());
    MiniGL::coordinateSystem();
   // MiniGL::drawPoint(Vector3D::Zero(),20,Color("white"));
    glPopMatrix();
  });
  
  doLights();
}
void LightRenderer::onBeforeRendering(){

}
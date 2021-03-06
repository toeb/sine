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
  if(!getRenderLight())return;
  foreachElement([this](Light * light){
    glPushMatrix();
    glTransformation(light->Coordinates());

    glMaterial(_Material);
    glScale(0.2);
    glSphere(0.01,15,15);
    glPopMatrix();
  });

  doLights();
}
void LightRenderer::onBeforeRendering(){
}
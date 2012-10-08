
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
    //glCoordinateSystem();
    Material m("PolishedGold");
    m.Shininess()=100;
    m.Emission()=m.Specular();

    glMaterial(m);
    glScale(0.2);
    glSphere(0.01,15,15);
    glPopMatrix();
  });
  
  doLights();
}
void LightRenderer::onBeforeRendering(){

}
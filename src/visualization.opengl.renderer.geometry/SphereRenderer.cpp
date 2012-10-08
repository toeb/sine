#include "SphereRenderer.h"

#include <visualization.opengl/opengl.h>
#include <visualization.opengl/Utility.h>

using namespace nspace;


void SphereRenderer::render(){
  Material material("Silver");
  foreachElement([&material](Sphere * sphere){
    glPushMatrix();
    glMaterial(material);
    glTransformation(sphere->coordinates());
    glSphere(sphere->radius(),20,20);
    glPopMatrix();
  });
}



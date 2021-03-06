#include "SphereRenderer.h"

#include <visualization.opengl/opengl.h>
#include <visualization.opengl/Utility.h>

using namespace nspace;

SphereRenderer::SphereRenderer():_LatitudeSegments(20),_LongitudeSegments(20){
  setColor(Color("green"));
  setName("SphereRenderer");
}

void SphereRenderer::render(){
  foreachElement([this](Sphere * sphere){
    glPushMatrix();
    glMaterial(getMaterial());
    glTransformation(sphere->coordinates());
    glSphere(sphere->radius(),getLatitudeSegments(),getLongitudeSegments());
    glPopMatrix();
  });
}




void SphereRenderer::propertyChanging(Material,Material){}

void SphereRenderer::propertyChanging(Color, Color){
  setMaterial(Material(newvalue));
}

void SphereRenderer::propertyChanging(int, LatitudeSegments){}

void SphereRenderer::propertyChanging(int, LongitudeSegments){}
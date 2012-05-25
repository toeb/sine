#include <Visualization/MiniGL.h>

#include "SphereRenderer.h"

using namespace IBDS;


void SphereRenderer::render(){
  static float color[4];
  color[0] = MiniGL::darkGreen[0];
  color[1] = MiniGL::darkGreen[1];
  color[2] = MiniGL::darkGreen[2];
  color[3] = 0.5;
  MiniGL::drawSphere(&(_sphere.getPosition()),_sphere.getRadius(),color);
}
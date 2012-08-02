#include <visualization/opengl/MiniGL.h>

#include "SphereRenderer.h"

using namespace nspace;


void SphereRenderer::render(){
  static float color[4];
  color[0] = MiniGL::darkGreen[0];
  color[1] = MiniGL::darkGreen[1];
  color[2] = MiniGL::darkGreen[2];
  color[3] = 0.2;
  _sphere.coordinates().calculateRotationMatrices();
  const Matrix3x3 & orientation =  _sphere.coordinates().getTransposedRotationMatrix();
  
  
  const Vector3D & pos = _sphere.coordinates().position();
  MiniGL::pushMatrix();
  MiniGL::translate(pos);
  MiniGL::multMatrix(orientation);

  MiniGL::drawSphere(&Vector3D::Zero(),_sphere.radius(),color);
  MiniGL::popMatrix();
}
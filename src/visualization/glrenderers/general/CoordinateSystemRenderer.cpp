#include "CoordinateSystemRenderer.h"

#include <visualization/opengl/MiniGL.h>

using namespace std;
using namespace nspace;

void CoordinateSystemRenderer::render(){
  MiniGL::pushMatrix();
  MiniGL::translate(_coordinateSystem.position());
  MiniGL::multMatrix(_coordinateSystem.orientation().getMatrix3x3());
  MiniGL::drawVector(Vector3D::Zero(), Vector3D::UnitX(),2,MiniGL::red);
  MiniGL::drawVector(Vector3D::Zero(), Vector3D::UnitY(),2,MiniGL::green);
  MiniGL::drawVector(Vector3D::Zero(), Vector3D::UnitZ(),2,MiniGL::blue);
  MiniGL::popMatrix();
}
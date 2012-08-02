#include "PointRenderer.h"
#include <visualization/opengl/MiniGL.h>

using namespace nspace;

PointRenderer::PointRenderer(const Vector3D & point):_pointCoordinates(point){

}

void PointRenderer::render(){
  MiniGL::drawPoint(_pointCoordinates,3,MiniGL::darkblue);
}